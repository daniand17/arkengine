#pragma once

#include "MaterialFactory.h"
#include "MeshFactory.h"

class ResourceManager
{
public:
	enum ResourceType
	{
		Model,
		Material
	};


	static ResourceManager * Instance() { return mInstance; }

private:
	static ResourceManager * mInstance;

	MeshFactory * mMeshFactory;
	MaterialFactory * mMaterialFactory;
};