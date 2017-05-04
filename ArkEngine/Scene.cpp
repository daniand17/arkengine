#include "Scene.h"

void Scene::instantiateGameObject(GameObject const * gameObject)
{
	GameObject * newGameObject = new GameObject(gameObject);

	Renderer * ren = newGameObject->getComponent<Renderer>();

	bool sceneChanged = false;

	if ( ren )
	{
		m_renderers.push_back(ren);
		m_gameObjects.push_back(newGameObject);
		sceneChanged = true;
		eventSystem->fireEvent(NotificationEvent::System_SceneChanged);
	}

}



void Scene::destroyGameObject(GameObject * gameObject)
{
}