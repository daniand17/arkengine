#pragma once
#include <vector>
#include "ArkRendering.h"

class MaterialFactory
{
public:
	ArkRendering::MaterialInfo * GetMaterialById(Resource_Id id) const { return id < mLoadedMaterials.size() ? mLoadedMaterials[id] : NULL; }	
	Resource_Id CreateMaterial();

private:
	std::vector<ArkRendering::MaterialInfo *> mLoadedMaterials;

};