#include "ModelFactory.h"

using namespace ArkRendering;
using namespace std;

Resource_Id ModelFactory::createModelFromMaterialAndMeshId(Resource_Id materialId, Resource_Id meshId)
{
	Resource_Id newId = mLoadedModels.size();

	for ( Resource_Id id = 0 ; id < newId ; id++ )
		if ( mLoadedModels[id].materialId == materialId && mLoadedModels[id].meshId == meshId )
			return mLoadedModels[id].id;

	ModelInfo newModel;
	newModel.id = newId;
	newModel.materialId = materialId;
	newModel.meshId = meshId;
	newModel.modelMatrix = Mat4::identity();
	mLoadedModels.push_back(newModel);

	return newModel.id;
}

void ModelFactory::GetUsedMaterialIds(std::vector<Resource_Id>& out) const
{
	for ( vector<ModelInfo>::const_iterator iter = mLoadedModels.begin() ; iter < mLoadedModels.end() ; iter++ )
	{
		Resource_Id toPush = iter->materialId;
		bool alreadyPushed = false;
		for ( int i = 0 ; i < out.size() ; i++ )
		{
			if ( out[i] == toPush )
			{
				alreadyPushed = true;
				break;
			}
		}

		if ( !alreadyPushed )
			out.push_back(toPush);
	}
}

void ModelFactory::SynchronizeResources(ArkString projectName)
{
}

void ModelFactory::DesynchronizeResources(ArkString projectName)
{
}

void ModelFactory::clear()
{
	mLoadedModels._Pop_back_n(mLoadedModels.size());
}
