#include <vector>
#include <mutex>
#include <set>
#include "ArkRendering.h"
#include "ArkThread.h"
#pragma once

class RendererModelManager
{
public:
	static void Initialize() { smInstance = new RendererModelManager();}
	static RendererModelManager * Instance() { return smInstance; }

	RendererModelManager();
	~RendererModelManager();

	void ReleaseModelInfoById(Resource_Id modelId);
	ArkRendering::ModelInfo * GetNextModelInfoForPopulate();
	size_t GetNumModels() const { return mModels.size(); }
	void getUsedMaterials(std::set<ArkString> &out) const;
	void getModelsUsingMaterial(ArkString material, std::vector<ArkRendering::ModelInfo> & out);

	bool IsDirty() const { return mModelsDirty; }
	void SetModelsUpdated() { mModelsDirty = false; }
	ArkThreading::ArkMutex * getLock() const { return m_lock; }


private:
	struct ModelAllocation
	{
		bool isFree = true;
		ArkRendering::ModelInfo modelInfo;
	};

	std::vector<Resource_Id> mAvailableModelIds;
	std::vector<ModelAllocation> mModels;

	ArkThreading::ArkMutex * m_lock;
	static RendererModelManager * smInstance;

	bool mModelsDirty;
};