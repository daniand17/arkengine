#pragma once

#include <vector>
#include "GameObject.h"
#include "ArkDirectory.h"
#include "Renderer.h"

class Scene : public ProjectResource
{
public:
	typedef std::vector<MeshRenderer *>::const_iterator MeshRendererIterator;
	Scene(ArkString name, ArkString filename);
	~Scene();
	void addGameObjectToScene(GameObject * gameObject);
	void destroyGameObject(GameObject * gameObject);

	bool getSceneChanged() const { return m_sceneChanged; }
	void setSceneChanged(bool set) { m_sceneChanged = set; }

	size_t getNumRenderers() const { return m_renderers.size(); }
	std::vector<Renderer *> getRenderers() const { return m_renderers; }

	// Inherited via Resource
	virtual void serialize() const override;
	virtual void deserialize() override;

private:
	std::vector<GameObject *> m_gameObjects;
	std::vector<Renderer *> m_renderers;
	bool m_sceneChanged;

	std::vector<SerializableRelationship> flattenTree() const;
	std::vector<GameObject *> unflattenObjectTree(std::vector<SerializableRelationship> &objs) const;
	std::vector<SerializableRelationship> genFlattenedObjectTree(ArkStringList &objectList) const;

	void getSceneObjectsForDeserialize(ArkString &absFilepath, ArkStringList &objectList) const;
	void clearScene();
	void flattenTree(GameObject * obj, std::vector<SerializableRelationship> & currResult, unsigned & currId, unsigned currParentId) const;
};