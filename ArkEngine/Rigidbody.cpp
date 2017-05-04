#include "Rigidbody.h"
#include "ArkEngineCore.h"

using namespace Physics;

Rigidbody::Rigidbody(GameObject * gameObject)
	: Component(gameObject)
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

ArkString Rigidbody::getJson() const
{
	return ArkString();
}

