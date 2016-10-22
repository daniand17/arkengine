#pragma once

#include <vector>
#include "ArkRendering.h"
#include "ArkString.h"
#include "ModelLoader.h"
#include "AbstractResourceFactory.h"

class MeshFactory : public ResourceFactory
{
public:
	Resource_Id LoadMesh(ArkString modelName);
	ArkRendering::MeshInfo * GetMeshById(Resource_Id id) const { return id < mLoadedMeshes.size() ? mLoadedMeshes[id].mesh : NULL; }

	virtual void SynchronizeResources(ArkString projectName) override;
	virtual void DesynchronizeResources(ArkString projectName) override;

private:
	struct LoadedMesh
	{
		ArkString name;
		ArkRendering::MeshInfo * mesh;
	};

	std::vector<LoadedMesh> mLoadedMeshes;

	Resource_Id getIdOfLoadedMesh(ArkString modelName, bool & found) const;

};