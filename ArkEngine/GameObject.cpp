#include "GameObject.h"
#include "ArkEngineCore.h"

GameObject::GameObject()
	:m_name("New Game Object")
{
	m_transform = new Transform();
}

GameObject::GameObject(GameObject const * gameObject)
	: m_name(gameObject->m_name)
{
	m_transform = new Transform(gameObject->m_transform);
	// TODO Move to a component factory
}

void GameObject::instantiate(GameObject const * obj, Vec3 position, Quaternion rotation)
{
	SceneManager * sceneManager = ArkEngineCore::Instance()->getSceneManager();

	if ( sceneManager )
		sceneManager->getCurrentScene()->instantiateGameObject(obj);

}

void GameObject::destroy(GameObject * object)
{

}

ArkString GameObject::toString()
{
	return m_name + ArkString(" (GameObject)");
}
