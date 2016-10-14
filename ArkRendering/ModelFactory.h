#pragma once
#include <vector>

#include "ArkRendering.h"

class ModelFactory
{
public:
	Resource_Id createModelFromMaterialAndMeshId(Resource_Id materialId, Resource_Id meshId);
	ArkRendering::ModelInfo GetModelById(Resource_Id id) const { return id < mLoadedModels.size() ? mLoadedModels[id] : ArkRendering::ModelInfo(); }


private:
	std::vector<ArkRendering::ModelInfo> mLoadedModels;
};