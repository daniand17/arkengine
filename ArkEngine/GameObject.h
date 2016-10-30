#pragma once
#include "ArkString.h"
#include "Transform.h"
#include "Component.h"
#include "Renderer.h"

#include <list>
#include <typeinfo>

class GameObject
{
public:
	GameObject();
	GameObject(GameObject const * gameObject);
	~GameObject() {}

	void instantiate(GameObject const * obj, Vec3 position, Quaternion rotation) const;
	void destroy(GameObject * object) const;
	Transform * getTransform() const { return m_transform; }

	size_t numComponents() const { return m_components.size(); }

	template <typename T> void addComponent();
	template <typename T> T * getComponent();
	template <typename T> void removeComponent();
	template <typename T> std::vector<T *> getComponents() const;

	void copyFrom(GameObject const * gameObject);

	ArkString toString();

private:
	void clearComponents();
	typedef std::list<Component *> ComponentCollection;
	Transform * m_transform;
	ArkString m_name;
	std::list<Component *> m_components;
};

template<typename T>
inline void GameObject::addComponent()
{
	m_components.push_back(new T(this));
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
			return comp;
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
inline std::vector<T*> GameObject::getComponents() const
{
	std::vector<T *> out;
	for ( ComponentCollection::const_iterator iter = m_components.begin()
		; iter != m_components.end()
		; iter++ )
	{
		T * casted = dynamic_cast<T *>(*iter);
		if ( casted != NULL )
			out.push_back(casted);
	}

	return out;
}
