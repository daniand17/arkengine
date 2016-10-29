#pragma once
#include "Vec3.h"
#include "Quaternion.h"

class Transform
{
public:
	Transform(Transform const * other);
	Transform();

	Vec3 getPosition() const { return m_position; }
	Quaternion getRotation() const { return m_rotation; }

	void setPosition(Vec3 position) { m_position = position; }
	void setRotation(Quaternion rotation) { m_rotation = rotation; }

private:
	Vec3 m_position;
	Quaternion m_rotation;
};