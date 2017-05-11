#include "SceneManager.h"
#include "ArkEngineCore.h"
#include "ProjectManager.h"

void SceneManager::openScene(Scene * scene)
{
	if ( m_currentScene )
	{
		closeOpenScene();
	}

	m_currentScene = scene;

	eventSystem->fireEvent(NotificationEvent::Scene_Opened, m_currentScene->getName());
}



void SceneManager::closeOpenScene()
{
	if ( m_currentScene )
	{
		m_currentScene->serialize();
		eventSystem->fireEvent(NotificationEvent::Scene_Closed, m_currentScene->getName());
		m_currentScene = NULL;
	}
}



void SceneManager::onNotify(NotificationEvent const * type)
{

	switch ( type->getType() )
	{
	case NotificationEvent::Project_ResourcesLoaded:
	{
		std::list<ProjectResource *> scenes = arkEngine->getResourceManager()->getResourcesByType(ProjectResource::RT_Scene);

		if ( scenes.size() > 0 )
		{
			openScene(dynamic_cast<Scene *>(*(scenes.begin())));
		}
	}
	break;
	case NotificationEvent::Project_Closed:
	{
		closeOpenScene();
	}
	break;
	}
}



ArkString SceneManager::getPathToSceneFile(Scene const * scene) const
{
	return arkEngine->getProjectManager()->getProjectRoot() + "scenes/" + scene->getName() + ".scene";
}



SceneManager::SceneManager()
	: m_currentScene(NULL)
{
	subscribeToEvent(NotificationEvent::Project_Closed);
	subscribeToEvent(NotificationEvent::Project_ResourcesLoaded);
}