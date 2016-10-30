#include "Rigidbody.h"


Rigidbody::Rigidbody(GameObject * gameObject)
	: Component(gameObject)
	, mass(1.0f)
	, drag(1.0f)
	, angularDrag(1.0f)
	, gravityScale(1.0f)
	, velocity(Vec3::zero())
	, angularVelocity(Vec3::zero())
	, unresolvedForce(Vec3::zero())
{
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

	unresolvedForce += force;// TODO not quite right
}

void Rigidbody::addTorque(Vec3 torque, Physics::ForceType forceType)
{
	// TODO Rigidbody::addTorque method stub
}

void Rigidbody::copyFrom(Component const * component)
{
	Rigidbody const * rb = dynamic_cast<Rigidbody const *>(component);
	
	mass = rb->mass;
	drag = rb->drag;
	angularDrag = rb->angularDrag;
	gravityScale = rb->gravityScale;

	velocity = rb->velocity;
	unresolvedForce = rb->unresolvedForce;
	angularVelocity = rb->angularVelocity;
	rotation = rb->rotation;
}

