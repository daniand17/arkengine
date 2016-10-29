#include "RendererModelManager.h"
#include "ArkDebug.h"

RendererModelManager * RendererModelManager::smInstance = NULL;

using namespace ArkRendering;
using namespace std;



RendererModelManager::RendererModelManager()
	: mModelsDirty(true)
	, m_lock(NULL)
{
	m_lock = new ArkThreading::ArkMutex();
	Debug::Log("Initialized RendererModelManager");
}



RendererModelManager::~RendererModelManager()
{
	delete m_lock;
	m_lock = 0;
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
	SCOPE_LOCKER lock(m_lock, "Get Next Model Info For Populate");
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
		mModels.push_back(modelAlloc);
		modelInfo = &(mModels[newBlockId].modelInfo);
	}

	mModelsDirty = true;

	return modelInfo;
}


void RendererModelManager::getUsedMaterials(std::set<ArkString> & out) const
{
	out.clear();
	SCOPE_LOCKER lock(m_lock, "Get used materials");
	for ( vector<ModelAllocation>::const_iterator iter = mModels.begin() ; iter < mModels.end() ; iter++ )
	{
		bool alreadyPushed = false;
		ArkString materialName = iter->modelInfo.m_material;
		if ( out.find(materialName) == out.end() )
			out.insert(materialName);
	}
}

void RendererModelManager::getModelsUsingMaterial(ArkString material, std::vector<ArkRendering::ModelInfo> & out)
{
	SCOPE_LOCKER lock(m_lock, "Get used models with material");
	for ( size_t i = 0 ; i < mModels.size() ; i++ )
	{
		if ( mModels[i].modelInfo.m_material == material )
			out.push_back(mModels[i].modelInfo);
	}
}
