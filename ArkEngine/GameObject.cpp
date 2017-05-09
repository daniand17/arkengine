#include "GameObject.h"
#include "ArkEngineCore.h"

using namespace std;

GameObject::GameObject(GameObject const * gameObject)
	: I_Serializable(CI_GameObject)
	, m_name(gameObject ? gameObject->m_name : "New Game Object")
{

	subscribeToEvent(NotificationEvent::Tick_Update);
	subscribeToEvent(NotificationEvent::Tick_FixedUpdate);

	m_transform = new Transform();
	copyFrom(gameObject);
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
	if ( !gameObject ) return;
	clearComponents();

	m_transform->copyFrom(gameObject->m_transform);

	std::list<Rigidbody *> rigidbodies = gameObject->getComponentsOfType<Rigidbody>();

	for ( std::list<Rigidbody *>::iterator it(rigidbodies.begin()) ; it != rigidbodies.end(); it++ )
	{
		Rigidbody * rb = new Rigidbody();
		rb->copyFrom(*it);
		m_components.push_back(rb);
	}

	std::list<MeshRenderer *> meshRenderers = gameObject->getComponentsOfType<MeshRenderer>();

	for ( std::list<MeshRenderer *>::iterator it(meshRenderers.begin()); it != meshRenderers.end() ; it++ )
	{
		MeshRenderer * renderer = new MeshRenderer();
		renderer->copyFrom(*it);
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



ArkString GameObject::serialize() const
{
	ArkString str(YAML_Generator::genObjectNameHeader("GameObject"));
	str += YAML_Generator::genStringProperty("m_name", m_name);
	return str;
}



void GameObject::deserialize(ArkString)
{
}
