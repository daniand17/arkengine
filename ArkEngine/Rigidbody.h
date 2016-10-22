#pragma once
#include "Vec3.h"
#include "Quaternion.h"
#include "Physics.h"

class Rigidbody
{
public:
	Vec3 position;
	Vec3 velocity;
	Vec3 angularVelocity;
	Quaternion rotation;

	float mass;
	float drag;
	float angularDrag;
	float gravityScale;

private:
	Vec3 mUnresolvedForce;

public:
	Rigidbody();

	~Rigidbody() { position = Vec3::zero(); velocity = Vec3::zero(); angularVelocity = Vec3::zero(); }

	// Physics
	void addForce(Vec3 force, Physics::ForceType forceType = Physics::ForceType::Force);
	void addTorque(Vec3 torque, Physics::ForceType forceType = Physics::ForceType::Force);
};