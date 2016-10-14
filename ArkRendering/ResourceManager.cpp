#include "ResourceManager.h"
#include "ArkDebug.h"

ResourceManager * ResourceManager::mInstance = NULL;

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
