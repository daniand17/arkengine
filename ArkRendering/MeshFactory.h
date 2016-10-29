#pragma once

#include <map>
#include "ArkRendering.h"
#include "ArkString.h"
#include "ModelLoader.h"
#include "AbstractResourceFactory.h"

class MeshFactory : public ResourceFactory
{
public:
	void LoadMesh(ArkString modelName);

	virtual void serializeResources() override;
	virtual void deserializeResources() override;
	virtual size_t size() const override { return m_loadedMeshes.size(); }
	virtual ArkRendering::MeshInfo * getResourceByName(ArkString name) override;
	virtual void clear() override;

private:

	typedef std::map<ArkString, ArkRendering::MeshInfo *> MeshCollection;
	typedef std::pair<ArkString, ArkRendering::MeshInfo *> MeshNamePair;

	MeshCollection m_loadedMeshes;
};