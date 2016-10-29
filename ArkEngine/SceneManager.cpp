#include "SceneManager.h"

SceneManager * SceneManager::sm_instance = 0;

void SceneManager::Initialize()
{
	if ( !sm_instance )
		sm_instance = new SceneManager();
}

SceneManager::SceneManager()
	:m_currentScene(NULL)
	, m_sceneDirectory(NULL)
{
}

void Scene::instantiateGameObject(GameObject const * gameObject)
{
	GameObject * newGameObject = new GameObject(gameObject);

	MeshRenderer * goComponent = newGameObject->getComponent<MeshRenderer>(); // TODO (AD) Should maybe be a template function
	if ( goComponent )
	{
		m_renderers.push_back((Renderer *) goComponent);
		m_gameObjects.push_back(newGameObject);
	}
	// TODO (AD) Add notifier service here
}

void Scene::destroyGameObject(GameObject * gameObject)
{
}

void Scene::deserializeScene(ArkFile * file)
{
}

void Scene::serializeScene(ArkFile * file)
{
}
