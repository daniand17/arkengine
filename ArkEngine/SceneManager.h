#pragma once
#include <vector>
#include "Filesystem.h"
#include "GameObject.h"
#include "Renderer.h"
class Scene
{
public:
	typedef std::vector<MeshRenderer *>::const_iterator MeshRendererIterator;
	Scene() : m_sceneChanged(false) {}
	void instantiateGameObject(GameObject const * gameObject);
	void destroyGameObject(GameObject * gameObject);

	void deserializeScene(ArkFile * file);
	void serializeScene(ArkFile * file);

	bool getSceneChanged() const { return m_sceneChanged; }
	void setSceneChanged(bool set) { m_sceneChanged = set; }

	size_t getNumRenderers() const { return m_renderers.size(); }
	std::vector<MeshRenderer *>::const_iterator getRendererIterator() const { return m_renderers.begin(); }
	std::vector<MeshRenderer *>::const_iterator getEnd() const { return m_renderers.end(); }

private:
	std::vector<GameObject *> m_gameObjects;
	std::vector<MeshRenderer *> m_renderers;

	bool m_sceneChanged;
};

class SceneManager
{
public:
	SceneManager();
	void setSceneDirectory(ArkDirectory * directory) { m_sceneDirectory = directory; }
	void openSceneByName(ArkString sceneName);
	void closeCurrentOpenScene();
	
	ArkDirectory * getSceneDirectory() const { return m_sceneDirectory; }
	Scene * getCurrentScene() const { return m_currentScene; }

private:
	Scene * m_currentScene;
	ArkDirectory * m_sceneDirectory;
};