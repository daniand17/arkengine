#pragma once

#include "ArkString.h"
class GameObject;
class Transform;
struct Mat4;

class Component
{
public:
	Component(GameObject * gameObject);
	Transform * getTransform() const;
	GameObject * getGameObject() const { return m_gameObject; }

	virtual ArkString toString() const = 0;
	virtual void copyFrom(Component const * component) = 0;
	virtual ArkString getJson() const = 0;

	Mat4 getModelMatrix() const;

protected:
	Transform * m_transform;
	GameObject * m_gameObject;
};