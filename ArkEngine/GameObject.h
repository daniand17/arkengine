#pragma once
#include "ArkString.h"
#include "Transform.h"
#include "Component.h"
#include "SystemNotifications.h"
#include "ISerializable.h"
#include "Rigidbody.h"
#include "Renderer.h"

#include <list>
#include <typeinfo>

class GameObject : public NotificationSubscriber, public I_Serializable
{
public:
	GameObject(GameObject const * gameObject = NULL);
	~GameObject();

	bool hasChildren() const { return m_components.size() > 0; }

	void setTransform(Transform * transform) { m_transform = transform; }
	Transform * getTransform() const { return m_transform; }

	size_t numComponents() const { return m_components.size(); }

	template <typename T> void addComponent();
	template <typename T> T * getComponent();
	template <typename T> void removeComponent();
	template <typename T> std::list<T *> getComponentsInChildren() const;

	void copyFrom(GameObject const * gameObject);

	void onNotify(NotificationEvent const * notifyService) override
	{
		switch ( notifyService->getType() )
		{
		case NotificationEvent::Tick_Update: update(); break;
		case NotificationEvent::Tick_FixedUpdate: fixedUpdate(); break;
		}
	}

	std::list<GameObject *> getChildren() const { return m_children; }
	std::list<Component *> getAllComponents() const { return m_components; }

	// Inherited via I_Serializable
	virtual ArkString serialize() const override;
	virtual void deserialize(ArkString) override;

	ArkString toString();

	void transferComponentToObject(Component * component)
	{
		for ( ComponentCollection::const_iterator it(m_components.begin()) ; it != m_components.end() ; it++ )
		{
			if ( (*it) == component )
			{
				return;
			}
		}

		m_components.push_back(component);
	}

	void addChild(GameObject * child);

protected:
	virtual void update() {}
	virtual void fixedUpdate() {}

private:
	void clearComponents();
	typedef std::list<Component *> ComponentCollection;
	Transform * m_transform;
	ArkString m_name;
	std::list<Component *> m_components;
	std::list<GameObject *> m_children;

	template <typename T> void getComponentsForGameObject(GameObject const * gameObject, std::list<T *> & components) const;
};



template<typename T>
inline void GameObject::addComponent()
{
	m_components.push_back(new T());
	// TODO (AD) Should register the component for updates
}



template<typename T>
inline T * GameObject::getComponent()
{
	for ( ComponentCollection::iterator iter = m_components.begin()
		; iter != m_components.end()
		; iter++ )
	{
		T * comp = dynamic_cast<T *>(*iter);
		if ( comp )
		{
			return comp;
		}
	}
	return NULL;
}



template<typename T>
inline void GameObject::removeComponent()
{
	// TODO (AD) Also should deregister the component from updates
	for ( ComponentCollection::iterator iter = m_components.begin()
		; iter != m_components.end()
		; iter++ )
	{

		if ( dynamic_cast<T*>(*iter) != NULL )
		{
			Component * c = *iter;
			m_components.erase(iter);
			delete c;
			return;
		}
	}
}



template<typename T>
inline std::list<T*> GameObject::getComponentsInChildren() const
{
	std::list<T *> components;

	getComponentsForGameObject(this, components);

	return components;
}



template<typename T>
void GameObject::getComponentsForGameObject(GameObject const * gameObject, std::list<T *> & components) const
{
	for ( std::list<Component *>::const_iterator it(gameObject->m_components.begin()); it != gameObject->m_components.end(); it++ )
	{
		T * casted = dynamic_cast<T *>(*it);
		if ( casted != NULL )
		{
			components.push_back(casted);
		}
	}

	for ( std::list<GameObject *>::const_iterator it(gameObject->m_children.begin()); it != gameObject->m_children.end(); it++ )
	{
		getComponentsForGameObject(*it, components);
	}
}