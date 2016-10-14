#include "ModelFactory.h"

using namespace ArkRendering;

Resource_Id ModelFactory::createModelFromMaterialAndMeshId(Resource_Id materialId, Resource_Id meshId)
{
	Resource_Id newId = mLoadedModels.size();

	for ( Resource_Id id = 0 ; id < newId ; id++ )
		if ( mLoadedModels[id].materialId == materialId && mLoadedModels[id].meshId == meshId )
			return mLoadedModels[id].id;

	ModelInfo newModel;
	newModel.id = newId;
	newModel.materialId = materialId;
	newModel.meshId = meshId;
	newModel.modelMatrix = Mat4::identity();
	mLoadedModels.push_back(newModel);

	return newModel.id;
}
