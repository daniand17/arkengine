#include "Component.h"
#include "GameObject.h"
#include "Mat4.h"

Component::Component(GameObject * gameObject)
	: m_gameObject(gameObject)
{
}

Transform * Component::getTransform() const { return m_gameObject ? m_gameObject->getTransform() : NULL; }

Mat4 Component::getModelMatrix() const
{
	return Mat4();	// TODO (AD) Get world transform matrix
}
