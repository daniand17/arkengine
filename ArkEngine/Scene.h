#pragma once

#include <vector>
#include "GameObject.h"
#include "ArkDirectory.h"
#include "Renderer.h"

class Scene : public Resource
{
public:
	typedef std::vector<MeshRenderer *>::const_iterator MeshRendererIterator;
	Scene() : m_sceneChanged(false) {}
	void instantiateGameObject(GameObject const * gameObject);
	void destroyGameObject(GameObject * gameObject);

	bool getSceneChanged() const { return m_sceneChanged; }
	void setSceneChanged(bool set) { m_sceneChanged = set; }

	size_t getNumRenderers() const { return m_renderers.size(); }
	std::vector<Renderer *> getRenderers() const { return m_renderers; }

	// Inherited via Resource
	virtual ArkString serialize() const override;
	virtual void deserialize() const override;

private:
	std::vector<GameObject *> m_gameObjects;
	std::vector<Renderer *> m_renderers;

	bool m_sceneChanged;
};