#include "ResourceManager.h"
#include "ResourceManager.h"
#include "ArkDebug.h"
#include "ArkAssert.h"

ResourceManager * ResourceManager::mInstance = NULL;
ArkThreading::ArkMutex ResourceManager::sm_lock;

ResourceManager::ResourceManager()
	: m_modelFactory(NULL)
	, m_materialFactory(NULL)
	, m_meshFactory(NULL)
{
	m_meshFactory = new MeshFactory();
	m_materialFactory = new MaterialFactory();
	m_modelFactory = new ModelFactory();
	m_shaderFactory = new ShaderFactory();

	Debug::Log("Initialized Resource Manager");
}

ResourceManager::~ResourceManager()
{
	delete m_meshFactory;
	delete m_materialFactory;
	delete m_modelFactory;
	delete m_shaderFactory;

	m_meshFactory = 0;
	m_materialFactory = 0;
	m_modelFactory = 0;
	m_shaderFactory = 0;
}

void ResourceManager::Initialize()
{
	mInstance = new ResourceManager();
}

void ResourceManager::deserializeResources(ArkString projectName)
{
	Debug::Log("Deserializing resources");
	sm_lock.lock();
	m_shaderFactory->clear();
	m_materialFactory->clear();
	m_meshFactory->clear();
	m_modelFactory->clear();

	m_shaderFactory->DesynchronizeResources(projectName);
	m_materialFactory->DesynchronizeResources(projectName);
	m_meshFactory->DesynchronizeResources(projectName);
	m_modelFactory->DesynchronizeResources(projectName);

	bindMaterialsToShaders();

	sm_lock.unlock();
}

void ResourceManager::serializeResources(ArkString projectName)
{
	sm_lock.lock();
	m_modelFactory->SynchronizeResources(projectName);
	m_meshFactory->SynchronizeResources(projectName);
	m_materialFactory->SynchronizeResources(projectName);
	m_shaderFactory->SynchronizeResources(projectName);
	sm_lock.unlock();
}

ArkRendering::Resource * ResourceManager::GetResourceByIdAndType(Resource_Id id, ResourceType type) const
{
	switch ( type )
	{
	case Mesh:
		return m_meshFactory->GetMeshById(id);
	case Model:
		return m_modelFactory->GetModelById(id);
	case Material:
		return m_materialFactory->GetMaterialById(id);
	}
	return NULL;
}

void ResourceManager::bindMaterialsToShaders()
{
	m_shaderFactory->compileShaders();

	for ( unsigned i = 0 ; i < m_materialFactory->size() ; i++ )
	{
		ArkRendering::MaterialInfo * mat = m_materialFactory->GetMaterialById(i);
		ArkRendering::ShaderProgram * shaderProgram = mat ? m_shaderFactory->GetShaderProgramByResourceId(mat->getShaderProgramId()) : NULL;

		ARK_ASSERT(shaderProgram != NULL, "Shader program should not be null");
		if ( shaderProgram )
			mat->setShaderProgram(shaderProgram);
	}
}
