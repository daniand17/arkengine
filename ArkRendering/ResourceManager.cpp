#include "ResourceManager.h"
#include "ArkDebug.h"

ResourceManager * ResourceManager::mInstance = NULL;
ArkThreading::ArkMutex ResourceManager::sm_lock;

ResourceManager::ResourceManager()
	: mModelFactory(NULL)
	, mMaterialFactory(NULL)
	, mMeshFactory(NULL)
{
	mMeshFactory = new MeshFactory();
	mMaterialFactory = new MaterialFactory();
	mModelFactory = new ModelFactory();
	mShaderFactory = new ShaderFactory();

	Debug::Log("Initialized Resource Manager");
}

ResourceManager::~ResourceManager()
{
	delete mMeshFactory;
	delete mMaterialFactory;
	delete mModelFactory;
	delete mShaderFactory;

	mMeshFactory = 0;
	mMaterialFactory = 0;
	mModelFactory = 0;
	mShaderFactory = 0;
}

void ResourceManager::Initialize()
{
	mInstance = new ResourceManager();
}

void ResourceManager::desynchronizeResources(ArkString projectName)
{
	sm_lock.lock();
	mShaderFactory->clear();
	mMaterialFactory->clear();
	mMeshFactory->clear();
	mModelFactory->clear();

	mShaderFactory->DesynchronizeResources(projectName);
	mMaterialFactory->DesynchronizeResources(projectName);
	mMeshFactory->DesynchronizeResources(projectName);
	mModelFactory->DesynchronizeResources(projectName);
	sm_lock.unlock();
}

void ResourceManager::synchronizeResources(ArkString projectName)
{
	sm_lock.lock();
	mModelFactory->SynchronizeResources(projectName);
	mMeshFactory->SynchronizeResources(projectName);
	mMaterialFactory->SynchronizeResources(projectName);
	mShaderFactory->SynchronizeResources(projectName);
	sm_lock.unlock();
}

ArkRendering::Resource * ResourceManager::GetResourceByIdAndType(Resource_Id id, ResourceType type) const
{
	switch ( type )
	{
	case Mesh:
		return mMeshFactory->GetMeshById(id);
	case Model:
		return mModelFactory->GetModelById(id);
	case Material:
		return mMaterialFactory->GetMaterialById(id);
	}
	return NULL;
}
