#include "Rigidbody.h"
#include "ArkEngineCore.h"

using namespace Physics;

Rigidbody::Rigidbody()
	: Component(CI_Rigidbody)
	, m_unresolvedForce(Vec3::zero())
{
	// TODO (AD) This needs to register with something somehow
	m_rigidbodyInfo = new RigidbodyInfo();
}



void Rigidbody::addForce(Vec3 force, Physics::ForceType forceType)
{
	switch ( forceType )
	{
	case Physics::ForceType::Acceleration:
		break;
	case Physics::ForceType::Force:
		break;
	case Physics::ForceType::Impulse:
		break;
	case Physics::ForceType::VelocityChange:
		break;
	}

	m_unresolvedForce += force;// TODO not quite right
}



void Rigidbody::addTorque(Vec3 torque, Physics::ForceType forceType)
{
	// TODO Rigidbody::addTorque stub
}



void Rigidbody::copyFrom(Component const * component)
{
	Rigidbody const * rb = dynamic_cast<Rigidbody const *>(component);
	
	RigidbodyInfo * rbInfo = rb->m_rigidbodyInfo;

	m_rigidbodyInfo->angularVelocity	= rbInfo->angularVelocity;
	m_rigidbodyInfo->gravityScale		= rbInfo->gravityScale;
	m_rigidbodyInfo->angularDrag		= rbInfo->angularDrag;
	m_rigidbodyInfo->velocity			= rbInfo->velocity;
	m_rigidbodyInfo->rotation			= rbInfo->rotation;
	m_rigidbodyInfo->mass				= rbInfo->mass;
	m_rigidbodyInfo->drag				= rbInfo->drag;

	m_unresolvedForce = rb->m_unresolvedForce;
}



ArkString Rigidbody::serialize() const
{
	ArkString str(YAML_Generator::genObjectNameHeader("Rigidbody"));
	str += YAML_Generator::genRawProperty("m_position",			m_rigidbodyInfo->position.toString());
	str += YAML_Generator::genRawProperty("m_rotation",			m_rigidbodyInfo->rotation.toString());
	str += YAML_Generator::genNumberProperty("m_mass",			m_rigidbodyInfo->mass);
	str += YAML_Generator::genNumberProperty("m_drag",			m_rigidbodyInfo->drag);
	str += YAML_Generator::genNumberProperty("m_angularDrag",	m_rigidbodyInfo->angularDrag);
	str += YAML_Generator::genNumberProperty("m_gravityScale",	m_rigidbodyInfo->gravityScale);
	return str;
}



void Rigidbody::deserialize(ArkString)
{
	// TODO (AD) Rigidbody deserialize stub
}

