#pragma once

#include <vector>
#include "ArkRendering.h"
#include "ArkString.h"
#include "ModelLoader.h"

class MeshFactory
{
public:
	Resource_Id LoadMesh(ArkString modelName);
	ArkRendering::MeshInfo * GetMeshById(Resource_Id id) const { return id < mLoadedMeshes.size() ? mLoadedMeshes[id].mesh : NULL; }

private:
	struct LoadedMesh
	{
		ArkString name;
		ArkRendering::MeshInfo * mesh;
	};

	std::vector<LoadedMesh> mLoadedMeshes;

	Resource_Id getIdOfLoadedMesh(ArkString modelName, bool & found) const;

};