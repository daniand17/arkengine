#include "MeshFactory.h"

#include "Filestream.h"

using namespace ArkRendering;

void MeshFactory::LoadMesh(ArkString modelName)
{
	if ( modelName.length() == 0 || m_loadedMeshes.find(modelName) != m_loadedMeshes.end() ) return;

	MeshInfo * meshInfo = new MeshInfo();

	if ( ModelLoading::loadOBJ(m_directory->getAbsolutePath() + modelName, meshInfo->vertices, meshInfo->uvs, meshInfo->normals) )
	{
		meshInfo->name = modelName;
		m_loadedMeshes.insert(MeshNamePair(modelName, meshInfo));
	}
	else
		delete meshInfo;
}


void MeshFactory::serializeResources()
{
	// TODO (AD) Might not need to serialize meshes because we are only reading from whats in the directory
}


void MeshFactory::deserializeResources()
{
	std::vector<ArkFile> const * fileList = m_directory->getFileList();
	for ( unsigned int i = 0 ; i < fileList->size() ; i++ )
		LoadMesh(fileList->at(i).getFilename());
}


ArkRendering::MeshInfo * MeshFactory::getResourceByName(ArkString name)
{
	auto iter = m_loadedMeshes.find(name);
	if ( iter != m_loadedMeshes.end() )
		return iter->second;
	return NULL;

}

void MeshFactory::clear()
{
	for ( auto iter = m_loadedMeshes.begin() ; iter != m_loadedMeshes.end() ; iter++ )
		delete iter->second;
	m_loadedMeshes.clear();
}