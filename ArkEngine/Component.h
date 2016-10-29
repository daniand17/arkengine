#pragma once

#include "ArkString.h"
class GameObject;
class Transform;

class Component
{
public:
	Component(GameObject * gameObject);
	Transform * getTransform() const;
	GameObject * getGameObject() const { return m_gameObject; }

	virtual ArkString toString() const = 0;

protected:
	Transform * m_transform;
	GameObject * m_gameObject;
};