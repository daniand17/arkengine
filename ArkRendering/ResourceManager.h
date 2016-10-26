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

	void serializeResources(ArkString projectName);
	void deserializeResources(ArkString projectName);
	ArkRendering::Resource * GetResourceByIdAndType(Resource_Id id, ResourceType type) const;
	MeshFactory * GetMeshFactory() const { return m_meshFactory; }
	MaterialFactory * GetMaterialFactory() const { return m_materialFactory; }
	ModelFactory * GetModelFactory() const { return m_modelFactory; }
	ShaderFactory * GetShaderFactory() const { return m_shaderFactory; }

	void bindMaterialsToShaders();

private:
	static ResourceManager * mInstance;
	static ArkThreading::ArkMutex sm_lock;

	MeshFactory *		m_meshFactory;
	MaterialFactory *	m_materialFactory;
	ModelFactory *		m_modelFactory;
	ShaderFactory *		m_shaderFactory;
};