#include "MeshFactory.h"

#include "Filestream.h"

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
		meshInfo->name = modelName;
		meshInfo->id = mLoadedMeshes.size();

		ModelLoading::loadOBJ(modelName, meshInfo->vertices, meshInfo->uvs, meshInfo->normals);

		LoadedMesh loadedMesh;
		loadedMesh.mesh = meshInfo;
		loadedMesh.name = modelName;
		mLoadedMeshes.push_back(loadedMesh);
		return meshInfo->id;
	}
}

void MeshFactory::SynchronizeResources(ArkString projectName)
{
	Filestream filestream(projectName, "meshes");
	filestream.OpenFile(Filestream::FileOpenType::Write);
	ArkString syncString("");

	for ( std::vector<LoadedMesh>::const_iterator iter = mLoadedMeshes.begin() ; iter < mLoadedMeshes.end() ; iter++ )
	{
		syncString += iter->mesh->Synchronize();

		if ( (iter + 1) < mLoadedMeshes.end() )
			syncString += "\n,";
	}
	filestream.WriteStringToFile(syncString);
	filestream.CloseFile();
}

void MeshFactory::DesynchronizeResources(ArkString projectName)
{
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
