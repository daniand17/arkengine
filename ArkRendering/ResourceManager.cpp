#include "ResourceManager.h"

ResourceManager * ResourceManager::mInstance = NULL;

ResourceManager::ResourceManager()
	: mModelFactory(NULL)
	, mMaterialFactory(NULL)
	, mMeshFactory(NULL)
{
	mMeshFactory = new MeshFactory();
	mMaterialFactory = new MaterialFactory();
	mModelFactory = new ModelFactory();
}

ResourceManager::~ResourceManager()
{
	delete mMeshFactory;
	delete mMaterialFactory;
	delete mModelFactory;

	mMeshFactory = 0;
	mMaterialFactory = 0;
	mModelFactory = 0;
}

void ResourceManager::Initialize()
{
	mInstance = new ResourceManager();

}

ArkRendering::Resource * ResourceManager::getResourceByIdAndType(Resource_Id id, ResourceType type) const
{
	
	switch ( type )
	{
	case Mesh:
		return mMeshFactory->GetMeshById(id);
	case Model:
		mModelFactory->GetModelById(id);
	case Material:
		mMaterialFactory->GetMaterialById(id);
	}

	return NULL;
}
