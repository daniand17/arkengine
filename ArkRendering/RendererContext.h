#include <vector>
#include <list>
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
		bool isFree;
		ArkRendering::MeshInfo * mesh;
		ArkRendering::MaterialInfo * material;
		Mat4 modelMatrix;

		AllocatedModel() : isFree(true), mesh(NULL), material(NULL) {}
	};

	RendererContext();
	~RendererContext();

	size_t GetNumModels() const { return m_models.size(); }
	void getUsedMaterials(std::set<ArkString> &out) const;
	void getModelsUsingMaterial(ArkString material, std::vector<AllocatedModel *> & out);

	bool IsDirty() const { return m_isDirty; }
	void setIsDirty() { m_isDirty = true; }
	void SetModelsUpdated() { m_isDirty = false; }
	ArkThreading::ArkMutex * getLock() const { return m_lock; }

	AllocatedModel * getModelForPopulate();

private:
	typedef std::list<AllocatedModel *> ModelList;

	std::list<AllocatedModel *> m_models;
	std::list<AllocatedModel *> m_freeModels;

	ArkThreading::ArkMutex * m_lock;
	static RendererContext * sm_instance;

	void clearUnusedMaterials();

	bool m_isDirty;
};