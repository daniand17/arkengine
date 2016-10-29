#pragma once
#include "ArkString.h"
#include "Transform.h"
#include "Component.h"
#include "Renderer.h"

#include <typeinfo>

class GameObject
{
public:
	GameObject();
	GameObject(GameObject const * gameObject);
	~GameObject() {}

	void instantiate(GameObject const * obj, Vec3 position, Quaternion rotation);
	void destroy(GameObject * object);
	Transform * getTransform() const { return m_transform; }
	
	template <typename T> T * getComponent();


private:
	Transform * m_transform;
	ArkString m_name;
	std::vector<Component *> m_components;
};

template<typename T>
inline T * GameObject::getComponent()
{
	for ( size_t i = 0 ; i < m_components.size() ; i++ )
	{
		T * comp = dynamic_cast<T *>(m_components.at(i));
		if ( comp )
			return comp;
	}

	return NULL;
}
