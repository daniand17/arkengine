#include "Transform.h"

Transform::Transform() 
	: Component(CI_Transform)
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



ArkString Transform::serialize() const
{
	ArkString str(YAML_Generator::genObjectNameHeader("Transform"));
	str += YAML_Generator::genRawProperty("m_position", m_position.toString());
	str += YAML_Generator::genRawProperty("m_rotation", m_rotation.toString());
	return str;
}



void Transform::deserialize(ArkString)
{

	// TODO (AD) Transform deserialize stub
}
