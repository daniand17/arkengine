#pragma once

#include "MaterialFactory.h"
#include "MeshFactory.h"
#include "ModelFactory.h"

class ResourceManager
{
public:
	enum ResourceType
	{
		Mesh,
		Model,
		Material
	};

	ResourceManager();
	~ResourceManager();
	static ResourceManager * Instance() { return mInstance; }
	static void Initialize();

	ArkRendering::Resource * getResourceByIdAndType(Resource_Id id, ResourceType type) const;
	MeshFactory * GetMeshFactory() const { return mMeshFactory; }
	MaterialFactory * GetMaterialFactory() const { return mMaterialFactory; }
	ModelFactory * GetModelFactory() const { return mModelFactory; }

private:
	static ResourceManager * mInstance;

	MeshFactory * mMeshFactory;
	MaterialFactory * mMaterialFactory;
	ModelFactory * mModelFactory;
};