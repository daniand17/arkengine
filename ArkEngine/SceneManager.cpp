#include "SceneManager.h"
#include "ArkEngineCore.h"
#include "ProjectManager.h"

void SceneManager::openSceneByName(ArkString sceneName)
{
	Scene * scene = new Scene();
	scene->setName(sceneName);

	ArkString rootPath(arkEngine->getProjectManager()->getProjectRoot() + "scenes/");

	ArkDirectory dir(rootPath);
	
	if ( !dir.exists() )
	{
		dir.mkpath();
	}

	ArkString filename(rootPath + sceneName + ".scene");
	ArkFile file(filename);

	if ( file.exists() )
	{
		scene->deserialize(filename);
	}
	else
	{
		file.mkfile();
	}

	if ( m_currentScene )
	{
		closeCurrentOpenScene();
	}

	m_currentScene = scene;

	GameObject * obj = new GameObject();
	obj->addComponent<MeshRenderer>();
	obj->addComponent<Rigidbody>();

	scene->instantiateGameObject(obj);

	closeCurrentOpenScene();
}



void SceneManager::closeCurrentOpenScene()
{
	m_currentScene->serialize(getPathToSceneFile(m_currentScene));
	eventSystem->fireEvent(NotificationEvent::System_SceneClosed);
}



void SceneManager::onNotify(NotificationEvent const * type)
{
	openSceneByName("New Scene");	// TODO (AD) eventually open last scene open
}



ArkString SceneManager::getPathToSceneFile(Scene const * scene) const
{
	return arkEngine->getProjectManager()->getProjectRoot() + "scenes/" + scene->getName() + ".scene";
}



SceneManager::SceneManager()
	: m_currentScene(NULL)
{
	subscribeToEvent(NotificationEvent::System_ProjectOpened);
	subscribeToEvent(NotificationEvent::System_ProjectClosed);
}