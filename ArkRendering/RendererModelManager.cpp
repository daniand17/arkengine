#include "RendererModelManager.h"

RendererModelManager * RendererModelManager::mInstance = NULL;

void RendererModelManager::ReleaseModelInfoById(Resource_Id modelId)
{
	mAvailableModelIds.push_back(modelId);
	mModels[modelId].isFree = true;
}

ArkRendering::ModelInfo * RendererModelManager::getModelInfoForPopulate()
{
	mLock.lock();
	size_t siz = mAvailableModelIds.size();
	if ( siz > 0 )
	{
		Resource_Id index = mAvailableModelIds[siz - 1];
		ModelAllocation & alloc = mModels[index];
		alloc.isFree = false;
		mAvailableModelIds.pop_back();
		mLock.unlock();
		return alloc.modelInfo;
	}
	else
	{
		ModelAllocation modelAlloc;
		modelAlloc.isFree = false;
		modelAlloc.modelInfo = new ArkRendering::ModelInfo();
		modelAlloc.modelInfo->id = static_cast<Resource_Id>(siz);
		mModels.push_back(modelAlloc);
		mLock.unlock();
		return modelAlloc.modelInfo;
	}
}
