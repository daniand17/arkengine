#pragma once
#include <vector>
#include "ArkRendering.h"
#include "AbstractResourceFactory.h"

class MaterialFactory : public ResourceFactory
{
public:
	ArkRendering::MaterialInfo * GetMaterialById(Resource_Id id) const { return id < mLoadedMaterials.size() ? mLoadedMaterials[id] : NULL; }
	Resource_Id CreateMaterial();

	void SynchronizeResources(ArkString projectName) override;
	void DesynchronizeResources(ArkString projectName) override;
	virtual size_t size() const override { return mLoadedMaterials.size(); }

private:
	typedef std::vector<ArkRendering::MaterialInfo *> MaterialInfoListT;
	MaterialInfoListT mLoadedMaterials;

	void createMaterialFromString(ArkString & materialString);
};