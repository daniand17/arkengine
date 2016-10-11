#include "MeshFactory.h"

using namespace ArkRendering;

ArkRendering::MeshInfo * MeshFactory::LoadMesh(ArkString modelName)
{
	bool loaded = false;
	int index = getIndexOfLoadedMesh(modelName);

	if ( index != DATA_NONE )
		return mLoadedMeshes[index].mesh;
	else
	{
		MeshInfo * meshInfo = new MeshInfo();
		meshInfo->id = mLoadedMeshes.size();

		ModelLoading::loadOBJ(modelName, meshInfo->vertices, meshInfo->uvs, meshInfo->normals);

		LoadedMesh loadedMesh;
		loadedMesh.mesh = meshInfo;
		loadedMesh.name = modelName;
		mLoadedMeshes.push_back(loadedMesh);
	}
}

int MeshFactory::getIndexOfLoadedMesh(ArkString modelName) const
{
	int index = DATA_NONE;
	for ( int i = 0 ; i < mLoadedMeshes.size() ; i++ )
	{
		if ( mLoadedMeshes[i].name == modelName )
		{
			index = i;
			break;
		}
	}

	return index;
}
