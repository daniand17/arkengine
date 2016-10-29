#pragma once

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

	void setProjectDirectory(ArkString directory) { m_projectDirectory = directory; }

	void serializeResources();
	void deserializeResources();
	ArkRendering::Resource * GetResourceByNameAndType(ArkString name, ResourceType type) const;
	MeshFactory * GetMeshFactory() const { return m_meshFactory; }
	MaterialFactory * GetMaterialFactory() const { return m_materialFactory; }
	ModelFactory * GetModelFactory() const { return m_modelFactory; }
	ShaderFactory * GetShaderFactory() const { return m_shaderFactory; }

	void bindMaterialsToShaders();

	ArkThreading::ArkMutex * getLock() const { return m_lock; }

private:
	static ResourceManager * mInstance;
	ArkThreading::ArkMutex * m_lock;

	ArkString m_projectDirectory;

	MeshFactory *		m_meshFactory;
	MaterialFactory *	m_materialFactory;
	ModelFactory *		m_modelFactory;
	ShaderFactory *		m_shaderFactory;
};