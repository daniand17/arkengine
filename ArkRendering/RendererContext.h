#include <vector>
#include <mutex>
#include <set>
#include "ArkRendering.h"
#include "ArkThread.h"
#pragma once

class RendererContext
{
public:
	struct AllocatedModel
	{
		ArkRendering::MeshInfo * mesh;
		ArkRendering::MaterialInfo * material;
	};

	static void Initialize() { smInstance = new RendererContext();}
	static RendererContext * Instance() { return smInstance; }

	RendererContext();
	~RendererContext();

	ArkRendering::ModelInfo * GetNextModelInfoForPopulate();
	size_t GetNumModels() const { return m_models.size(); }
	void getUsedMaterials(std::set<ArkString> &out) const;
	void getModelsUsingMaterial(ArkString material, std::vector<AllocatedModel> & out);

	bool IsDirty() const { return m_isDirty; }
	void setIsDirty() { m_isDirty = true; }
	void SetModelsUpdated() { m_isDirty = false; }
	ArkThreading::ArkMutex * getLock() const { return m_lock; }

	bool materialAlreadyInContext(ArkRendering::MaterialInfo * material) const;
	void addMaterial(ArkRendering::MaterialInfo const * materialInfo);

	void addModelToContext(AllocatedModel model);

private:
	std::vector<AllocatedModel> m_models;
	std::vector<ArkRendering::MaterialInfo> m_usedMaterials;

	ArkThreading::ArkMutex * m_lock;
	static RendererContext * smInstance;

	void clearUnusedMaterials();

	bool m_isDirty;
};