#include "SceneManager.h"
#include "ArkEngineCore.h"

void SceneManager::openSceneByName(ArkString sceneName)
{
	Scene * scene = new Scene();

	ArkDirectory dir(m_scenePath);
	if ( dir.fileExists(sceneName + ".scene") )
	{
		//scene->deserializeScene(dir.getFileByFilename(sceneName + ".scene"));
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
	subscribeToEvent(NotificationEvent::System_ProjectOpened);
	subscribeToEvent(NotificationEvent::System_ProjectClosed);
}