#include "ModelFactory.h"

using namespace ArkRendering;
using namespace std;

void ModelFactory::createModelFromMaterialAndMesh(ArkString modelName, ArkString materialName, ArkString meshName)
{
	ModelInfo newModel;
	newModel.m_name = modelName;
	newModel.m_material = materialName;
	newModel.m_mesh = meshName;
	m_loadedModels.insert(ModelNamePair(modelName, newModel));
}

void ModelFactory::GetUsedMaterials(ArkStringList list) const
{
	// TODO (AD) Implement get used materials (perhaps this should go into a scene manager?)
}

void ModelFactory::serializeResources()
{
	// TODO (AD) Implement serializeResources() for model factory
}

void ModelFactory::deserializeResources()
{
	// TODO (AD) implement desieralizeResources() for model factory
}

void ModelFactory::clear()
{
	m_loadedModels.clear();
}

ArkRendering::ModelInfo * ModelFactory::getResourceByName(ArkString name)
{
	auto iter = m_loadedModels.find(name);
	return iter != m_loadedModels.end() ? &(iter->second) : NULL;
}
