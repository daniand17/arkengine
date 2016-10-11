#include <vector>
#include <mutex>

#include "ArkRendering.h"

#pragma once

class RendererModelManager
{
public:
	static void Initialize() { mInstance = new RendererModelManager(); }
	static RendererModelManager * Instance() { return mInstance; }

	void ReleaseModelInfoById(Resource_Id modelId);
	ArkRendering::ModelInfo * getModelInfoForPopulate();

private:
	std::mutex mLock;

	struct ModelAllocation
	{
		bool isFree = true;
		ArkRendering::ModelInfo * modelInfo;
	};

	std::vector<Resource_Id> mAvailableModelIds;
	std::vector<ModelAllocation> mModels;

	static RendererModelManager * mInstance;
};