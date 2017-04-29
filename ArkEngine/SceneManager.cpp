#include "SceneManager.h"
#include "ArkEngineCore.h"


void SceneManager::openSceneByName(ArkString sceneName)
{
	Scene * scene = new Scene();

	ArkDirectory dir(m_scenePath);
	if ( dir.fileExists(sceneName + ".scene") )
	{
		scene->deserializeScene(dir.getFileByFilename(sceneName + ".scene"));
	}

	if ( m_currentScene )
		closeCurrentOpenScene();

	m_currentScene = scene;
}



void SceneManager::closeCurrentOpenScene()
{
}

void SceneManager::onNotify(NotificationEvent const * type)
{
	openSceneByName("New Scene");	// TODO (AD) eventually open last scene open
}



SceneManager::SceneManager()
	: m_currentScene(NULL)
	, m_scenePath("")
{
	subscribeToEvent(NotificationEvent::System_ProjectLoaded);
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
		eventSystem->fireEvent(NotificationEvent::System_SceneChanged);
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
