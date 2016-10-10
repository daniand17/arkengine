#include <vector>

#include "ArkRendering.h"

#pragma once

typedef unsigned int Resource_Id;

class RendererModelManager
{

public:
	void ReleaseModelInfoById(Resource_Id modelId);
	ArkRendering::ModelInfo * getModelInfoForPopulate();

private:
	struct ModelAllocation
	{
		bool isFree = true;
		ArkRendering::ModelInfo * modelInfo;
	};

	unsigned int numModels = 0;
	std::vector<Resource_Id> mAvailableModelIds;
	std::vector<ModelAllocation> mModels;
};