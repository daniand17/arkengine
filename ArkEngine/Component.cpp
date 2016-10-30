#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject * gameObject)
	: m_gameObject(gameObject)
{
}

Transform * Component::getTransform() const { return m_gameObject ? m_gameObject->getTransform() : NULL; }