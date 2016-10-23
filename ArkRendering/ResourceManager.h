#pragma once

#include <mutex>

#include "MaterialFactory.h"
#include "MeshFactory.h"
#include "ModelFactory.h"
#include "ShaderFactory.h"
#include "ArkThread.h"

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

	void synchronizeResources(ArkString projectName);
	void desynchronizeResources(ArkString projectName);
	ArkRendering::Resource * GetResourceByIdAndType(Resource_Id id, ResourceType type) const;
	MeshFactory * GetMeshFactory() const { return mMeshFactory; }
	MaterialFactory * GetMaterialFactory() const { return mMaterialFactory; }
	ModelFactory * GetModelFactory() const { return mModelFactory; }
	ShaderFactory * GetShaderFactory() const { return mShaderFactory; }

private:
	static ResourceManager * mInstance;
	static ArkThreading::ArkMutex sm_lock;

	MeshFactory * mMeshFactory;
	MaterialFactory * mMaterialFactory;
	ModelFactory * mModelFactory;
	ShaderFactory * mShaderFactory;
};