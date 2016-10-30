#pragma once
#include <vector>
#include "Filesystem.h"
#include "GameObject.h"
#include "Renderer.h"

class Scene
{
public:
	void instantiateGameObject(GameObject const * gameObject);
	void destroyGameObject(GameObject * gameObject);

	void deserializeScene(ArkFile * file);
	void serializeScene(ArkFile * file);

private:
	std::vector<GameObject *> m_gameObjects;
	std::vector<Renderer *> m_renderers;
};

class SceneManager
{
public:
	static void Initialize();
	static SceneManager * Instance() { return sm_instance; }

	SceneManager();
	void setSceneDirectory(ArkDirectory * directory) { m_sceneDirectory = directory; }
	void openSceneByName(ArkString sceneName);
	void closeCurrentOpenScene();
	
	ArkDirectory * getSceneDirectory() const { return m_sceneDirectory; }
	Scene * getCurrentScene() const { return m_currentScene; }

private:
	static SceneManager * sm_instance;
	Scene * m_currentScene;

	ArkDirectory * m_sceneDirectory;
};