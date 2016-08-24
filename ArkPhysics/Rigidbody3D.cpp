#include "Rigidbody.h"
#include "Time.h"

void Rigidbody::addForce(Vec3 force, ForceType forceType)
{
	switch ( forceType )
	{
	case ForceType::Acceleration:
		break;
	case ForceType::Force:
		velocity = (force / mass) * Time::deltaTime;
		break;
	case ForceType::Impulse:
		break;
	case ForceType::VelocityChange:
		break;
	}
}

void Rigidbody::addTorque(Vec3 torque, ForceType forceType)
{

}
