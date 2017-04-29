#pragma once
#include <map>
#include <string>
#include "ArkRendering.h"
#include "AbstractResourceFactory.h"

class ModelFactory : public ResourceFactory
{
public:
	void createModelFromMaterialAndMesh(ArkString modelName, ArkString materialName, ArkString meshName);
	void GetUsedMaterials(ArkStringList list) const;

	void serializeResources() override;
	void deserializeResources() override;
	virtual unsigned int size() const override { return m_loadedModels.size(); }
	virtual void clear() override;
	virtual ArkRendering::ModelInfo * getResourceByName(ArkString name) override;

private:
	typedef std::map<ArkString, ArkRendering::ModelInfo> ModelCollection;
	typedef std::pair<ArkString, ArkRendering::ModelInfo> ModelNamePair;
	ModelCollection m_loadedModels;
};