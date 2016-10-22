#pragma once
#include <vector>

#include "ArkRendering.h"
#include "AbstractResourceFactory.h"

class ModelFactory : public ResourceFactory
{
public:
	Resource_Id createModelFromMaterialAndMeshId(Resource_Id materialId, Resource_Id meshId);
	ArkRendering::ModelInfo * GetModelById(Resource_Id id) { return id < mLoadedModels.size() ? &mLoadedModels[id] : NULL; }
	void GetUsedMaterialIds(std::vector<Resource_Id> & out) const;

	void SynchronizeResources(ArkString projectName) override;
	void DesynchronizeResources(ArkString projectName) override;
private:
	std::vector<ArkRendering::ModelInfo> mLoadedModels;
};