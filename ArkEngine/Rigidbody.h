#pragma once
#include "ArkString.h"
#include "Vec3.h"
#include "Quaternion.h"
#include "Physics.h"
#include "Component.h"

class Rigidbody : public Component
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

	Rigidbody(GameObject * gameObject);

	~Rigidbody() { position = Vec3::zero(); velocity = Vec3::zero(); angularVelocity = Vec3::zero(); }

	// Physics
	void addForce(Vec3 force, Physics::ForceType forceType = Physics::ForceType::Force);
	void addTorque(Vec3 torque, Physics::ForceType forceType = Physics::ForceType::Force);

	ArkString toString() const override { return ArkString("Rigidbody"); }
	void copyFrom(Component const * component) override;
	ArkString getJson() const override;

private:
	Vec3 unresolvedForce;
};