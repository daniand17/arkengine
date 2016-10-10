#include "RendererResourceManager.h"

void RendererModelManager::ReleaseModelInfoById(Resource_Id modelId)
{
	mAvailableModelIds.push_back(modelId);
	mModels[modelId].isFree = true;
}

ArkRendering::ModelInfo * RendererModelManager::getModelInfoForPopulate()
{
	size_t siz = mAvailableModelIds.size();
	if ( siz > 0 )
	{
		Resource_Id index = mAvailableModelIds[siz - 1];
		mAvailableModelIds.pop_back();

		ModelAllocation & alloc = mModels[index];
		alloc.isFree = false;
		return alloc.modelInfo;
	}
	else
	{
		ModelAllocation modelAlloc;
		modelAlloc.isFree = false;
		modelAlloc.modelInfo = new ArkRendering::ModelInfo();
		modelAlloc.modelInfo->id = siz;
		mModels.push_back(modelAlloc);
		return modelAlloc.modelInfo;
	}
}
