#pragma once

#include <vector>
#include "GameObject.h"
#include "Filesystem.h"
#include "Renderer.h"


class Scene
{
public:
	typedef std::vector<MeshRenderer *>::const_iterator MeshRendererIterator;
	Scene() : m_sceneChanged(false) {}
	void instantiateGameObject(GameObject const * gameObject);
	void destroyGameObject(GameObject * gameObject);

	bool getSceneChanged() const { return m_sceneChanged; }
	void setSceneChanged(bool set) { m_sceneChanged = set; }

	size_t getNumRenderers() const { return m_renderers.size(); }

private:
	std::vector<GameObject *> m_gameObjects;
	std::vector<Renderer *> m_renderers;

	bool m_sceneChanged;
};
