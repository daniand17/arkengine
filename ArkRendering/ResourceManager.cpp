#include "ResourceManager.h"
#include "ArkDebug.h"
#include "ArkAssert.h"

using namespace ArkThreading;
using namespace ArkRendering;

ResourceManager::ResourceManager()
	: m_modelFactory(NULL)
	, m_materialFactory(NULL)
	, m_meshFactory(NULL)
	, m_lock(NULL)
{
	m_lock = new ArkMutex();

	m_meshFactory = new MeshFactory();
	m_materialFactory = new MaterialFactory();
	m_modelFactory = new ModelFactory();
	m_shaderFactory = new ShaderFactory();

	Debug::Log("Initialized Resource Manager");
}

ResourceManager::~ResourceManager()
{
	delete m_lock;
	delete m_meshFactory;
	delete m_materialFactory;
	delete m_modelFactory;
	delete m_shaderFactory;

	m_meshFactory = 0;
	m_materialFactory = 0;
	m_modelFactory = 0;
	m_shaderFactory = 0;
}



void ResourceManager::deserializeResources()
{
	SCOPE_LOCKER lock(getLock(), "Deserialize ResourceManager");
	m_shaderFactory->clear();
	m_materialFactory->clear();
	m_meshFactory->clear();
	m_modelFactory->clear();

	m_shaderFactory->deserializeResources();
	m_materialFactory->deserializeResources();
	m_meshFactory->deserializeResources();
	m_modelFactory->deserializeResources();

	bindMaterialsToShaders();
}

void ResourceManager::serializeResources()
{
	SCOPE_LOCKER lock(getLock(), "Serialize ResourceManager");
	m_modelFactory->serializeResources();
	m_meshFactory->serializeResources();
	m_materialFactory->serializeResources();
	m_shaderFactory->serializeResources();
}

ArkRendering::Resource * ResourceManager::GetResourceByNameAndType(ArkString name, ResourceType type) const
{
	switch ( type )
	{
	case Mesh: return m_meshFactory->getResourceByName(name);
	case Model: return m_modelFactory->getResourceByName(name);
	case Material: return m_materialFactory->getResourceByName(name);
	}
	return NULL;
}

void ResourceManager::bindMaterialsToShaders()
{
	m_shaderFactory->compileShaders();

	std::vector<ArkRendering::MaterialInfo *> mats;
	m_materialFactory->getAllMaterials(mats);

	for ( unsigned int i = 0 ; i < mats.size() ; i++ )
	{
		MaterialInfo * matInfo = mats.at(i);
		ShaderProgram * shader = m_shaderFactory->getResourceByName(matInfo->getShaderName());
		matInfo->setShaderProgram(shader);
	}
}
