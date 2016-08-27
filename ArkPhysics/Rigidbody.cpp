#include "Rigidbody.h"

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

	mUnresolvedForce += force;// TODO not quite right
}

void Rigidbody::addTorque(Vec3 torque, Physics::ForceType forceType)
{

}