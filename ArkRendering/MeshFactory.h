#pragma once

#include <vector>
#include "ArkRendering.h"
#include "ArkString.h"
#include "ModelLoader.h"

class MeshFactory
{
public:
	ArkRendering::MeshInfo * LoadMesh(ArkString modelName);
	

private:
	struct LoadedMesh
	{
		ArkString name;
		ArkRendering::MeshInfo * mesh;
	};

	std::vector<LoadedMesh> mLoadedMeshes;

	int getIndexOfLoadedMesh(ArkString modelName) const;

};