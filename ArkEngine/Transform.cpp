#include "Transform.h"

Transform::Transform(Transform const * other)
{
	m_position = other->m_position;
	m_rotation = other->m_rotation;
}

Transform::Transform() : m_position(Vec3(0, 0, 0))
{
	// TODO default initializer for rotation
}
