#include "MeshFactory.h"

using namespace ArkRendering;

Resource_Id MeshFactory::LoadMesh(ArkString modelName)
{
	bool loaded = false;
	Resource_Id index = getIdOfLoadedMesh(modelName, loaded);

	if ( loaded )
		return index;
	else
	{
		MeshInfo * meshInfo = new MeshInfo();
		meshInfo->id = mLoadedMeshes.size();

		ModelLoading::loadOBJ(modelName, meshInfo->vertices, meshInfo->uvs, meshInfo->normals);

		LoadedMesh loadedMesh;
		loadedMesh.mesh = meshInfo;
		loadedMesh.name = modelName;
		mLoadedMeshes.push_back(loadedMesh);
		return meshInfo->id;
	}
}

Resource_Id MeshFactory::getIdOfLoadedMesh(ArkString modelName, bool & found) const
{
	found = false;
	int index = DATA_NONE;
	for ( int i = 0 ; i < mLoadedMeshes.size() ; i++ )
	{
		if ( mLoadedMeshes[i].name == modelName )
		{
			index = i;
			found = true;
			break;
		}
	}

	return index;
}
