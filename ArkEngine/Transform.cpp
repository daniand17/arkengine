#include "Transform.h"

Transform::Transform(GameObject * gameObject) 
	: Component(m_gameObject)
	, m_position(Vec3(0, 0, 0))
{
	
	// TODO default initializer for rotation
}


void Transform::copyFrom(Component const * component)
{
	Transform const * trans = dynamic_cast<Transform const *>(component);
	m_position = trans->m_position;
	m_rotation = trans->m_rotation;
}
