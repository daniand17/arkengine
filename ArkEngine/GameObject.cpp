#include "GameObject.h"
#include "ArkEngineCore.h"
#include "Rigidbody.h"

using namespace std;

GameObject::GameObject()
	:m_name("New Game Object")
{
	m_transform = new Transform(this);
}


GameObject::GameObject(GameObject const * gameObject)
	: m_name(gameObject->m_name)
{
	m_transform = new Transform(this);
	copyFrom(gameObject);
	// TODO Move to a component factory
}


void GameObject::instantiate(GameObject const * obj, Vec3 position, Quaternion rotation) const
{
	SceneManager * sceneManager = ArkEngineCore::Instance()->getSceneManager();
	if ( sceneManager )
	{
		Scene * scene = sceneManager->getCurrentScene();
		if ( scene )
		{
			scene->instantiateGameObject(obj);
		}
	}
}


void GameObject::destroy(GameObject * object) const
{

}


void GameObject::copyFrom(GameObject const * gameObject)
{
	clearComponents();

	m_transform->copyFrom(gameObject->m_transform);

	std::vector<Rigidbody *> rigidbodies = gameObject->getComponents<Rigidbody>();

	for ( size_t i = 0 ; i < rigidbodies.size() ; i++ )
	{
		Rigidbody * rb = new Rigidbody(this);
		rb->copyFrom(rigidbodies[i]);
		m_components.push_back(rb);
	}

	std::vector<MeshRenderer *> meshRenderers = gameObject->getComponents<MeshRenderer>();

	for ( size_t i = 0 ; i < meshRenderers.size() ; i++)
	{
		MeshRenderer * renderer = new MeshRenderer(this);
		renderer->copyFrom(meshRenderers[i]);
		m_components.push_back(renderer);
	}
}


ArkString GameObject::toString()
{
	return m_name + ArkString(" (GameObject)");
}

void GameObject::clearComponents()
{
	for ( ComponentCollection::iterator i = m_components.begin() ; i != m_components.end() ; i++ )
	{
		Component * comp = *i;
		m_components.erase(i);
		delete comp;
	}
}
