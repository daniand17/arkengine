#pragma once
#include <map>
#include "ArkRendering.h"
#include "AbstractResourceFactory.h"

class MaterialFactory : public ResourceFactory
{
public:
	void CreateMaterial(ArkString name, ArkString shaderName);

	void serializeResources() override;
	void deserializeResources() override;
	void MaterialFactory::clear() override	{ m_loadedMaterials.clear(); }
	virtual unsigned int size() const override	{ return m_loadedMaterials.size(); }

	ArkRendering::MaterialInfo * getResourceByName(ArkString name) override;
	void getAllMaterials(std::vector<ArkRendering::MaterialInfo *> & out);

private:
	void createMaterialFromString(ArkString & materialString);

	typedef std::map<ArkString, ArkRendering::MaterialInfo> MaterialCollection;
	typedef std::pair<ArkString, ArkRendering::MaterialInfo> MaterialNamePair;
	MaterialCollection m_loadedMaterials;
};