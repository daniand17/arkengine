#include "RendererModelManager.h"
#include "ArkDebug.h"

RendererModelManager * RendererModelManager::smInstance = NULL;

using namespace ArkRendering;
using namespace std;

RendererModelManager::RendererModelManager()
	: mModelsDirty(true)
{
	Debug::Log("Initialized RendererModelManager");
}

RendererModelManager::~RendererModelManager()
{
}

void RendererModelManager::ReleaseModelInfoById(Resource_Id modelId)
{
	if ( modelId < mModels.size() )
	{
		mAvailableModelIds.push_back(modelId);
		mModels[modelId].isFree = true;
		mModelsDirty = true;
	}
}

ArkRendering::ModelInfo * RendererModelManager::GetNextModelInfoForPopulate()
{
	mLock.lock();
	ModelInfo * modelInfo;

	size_t siz = mAvailableModelIds.size();
	// There is already a free block
	if ( siz > 0 )
	{

		Resource_Id index = mAvailableModelIds[siz - 1];
 		ModelAllocation & alloc = mModels[index];
		alloc.isFree = false;
		mAvailableModelIds.pop_back();
		modelInfo = &mModels[index].modelInfo;
	}
	// Need to create a new block
	else
	{
		Resource_Id newBlockId = static_cast<Resource_Id>(mModels.size());
		ModelAllocation modelAlloc;
		modelAlloc.isFree = false;
		modelAlloc.modelInfo.id = newBlockId;
		mModels.push_back(modelAlloc);
		modelInfo = &(mModels[newBlockId].modelInfo);
	}

	mModelsDirty = true;

	mLock.unlock();
	return modelInfo;
}

void RendererModelManager::GetModelsWithMaterialId(Resource_Id materialId, std::vector<ArkRendering::ModelInfo>& out)
{
	mLock.lock();
	for ( Resource_Id i = 0 ; i < mModels.size() ; i++ )
		if ( mModels[i].modelInfo.materialId == materialId )
			out.push_back(mModels[i].modelInfo);
	mLock.unlock();
}

void RendererModelManager::GetUsedMaterialIds(std::vector<Resource_Id>& out) const
{
	for ( vector<ModelAllocation>::const_iterator iter = mModels.begin() ; iter < mModels.end() ; iter++ )
	{
		Resource_Id toPush = iter->modelInfo.materialId;
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
