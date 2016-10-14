#include <vector>
#include <mutex>

#include "ArkRendering.h"

#pragma once

class RendererModelManager
{
public:
	static void Initialize() { smInstance = new RendererModelManager();}
	static RendererModelManager * Instance() { return smInstance; }

	RendererModelManager();
	~RendererModelManager();

	void ReleaseModelInfoById(Resource_Id modelId);
	ArkRendering::ModelInfo * GetNextModelInfoForPopulate();
	void GetModelsWithMaterialId(Resource_Id materialId, std::vector<ArkRendering::ModelInfo> & out);
	size_t GetNumModels() const { return mModels.size(); }

private:
	struct ModelAllocation
	{
		bool isFree = true;
		ArkRendering::ModelInfo modelInfo;
	};

	std::vector<Resource_Id> mAvailableModelIds;
	std::vector<ModelAllocation> mModels;

	std::mutex mLock;
	static RendererModelManager * smInstance;

	bool mModelsDirty;
};