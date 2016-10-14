#include "MaterialFactory.h"

Resource_Id MaterialFactory::CreateMaterial()
{
	ArkRendering::MaterialInfo * material = new ArkRendering::MaterialInfo();
	material->id = mLoadedMaterials.size();
	material->ambient = Vec3(1, 1, 1);
	material->diffuse = Vec3(1, 1, 1);
	material->specular = Vec3(1, 1, 1);
	material->shininess = 32;

	mLoadedMaterials.push_back(material);

	return material->id;
}
