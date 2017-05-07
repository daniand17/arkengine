#include "Scene.h"
#include "ArkEngineCore.h"
void Scene::instantiateGameObject(GameObject const * gameObject)
{
	GameObject * newGameObject = new GameObject(gameObject);

	Renderer * ren = newGameObject->getComponent<Renderer>();

	if ( ren )
	{
		m_renderers.push_back(ren);
		m_gameObjects.push_back(newGameObject);
	} // NOTE (AD) This is where we might push back colliders
}



void Scene::destroyGameObject(GameObject * gameObject)
{
}



void Scene::serialize(ArkString absFilepath) const
{
}



void Scene::deserialize(ArkString absFilepath) const
{
}
