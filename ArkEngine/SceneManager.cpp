#include "SceneManager.h"
#include "ArkEngineCore.h"


void SceneManager::openSceneByName(ArkString sceneName)
{
	Scene * scene = new Scene();
	if ( m_sceneDirectory->fileExists(sceneName + ".scene") )
	{
		scene->deserializeScene(m_sceneDirectory->getFileByFilename(sceneName + ".scene"));
	}

	if ( m_currentScene )
		closeCurrentOpenScene();

	m_currentScene = scene;
}



void SceneManager::closeCurrentOpenScene()
{
}



SceneManager::SceneManager()
	:m_currentScene(NULL)
	, m_sceneDirectory(NULL)
{
}



void Scene::instantiateGameObject(GameObject const * gameObject)
{
	GameObject * newGameObject = new GameObject(gameObject);

	MeshRenderer * ren = newGameObject->getComponent<MeshRenderer>(); // TODO (AD) Should maybe be a template function

	bool sceneChanged = false;

	if ( ren )
	{
		m_renderers.push_back((MeshRenderer *) ren);
		m_gameObjects.push_back(newGameObject);
		sceneChanged = true;
	}

	if ( sceneChanged )
	{
		m_sceneChanged = true;
		ArkEngineCore * engine = ArkEngineCore::Instance();
		SystemNotificationBus * bus = engine ? engine->getNotificationBus() : NULL;

		if ( bus )
			bus->fireNotify(SystemNotifications::ServiceTypes::OnSceneChanged);
	}
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