#pragma once
#include "ArkString.h"
#include "Vec3.h"
#include "Quaternion.h"
#include "Physics.h"
#include "Component.h"

class Rigidbody : public Component
{
public:
	Rigidbody(GameObject * gameObject);

	// Physics
	void addForce(Vec3 force, Physics::ForceType forceType = Physics::ForceType::Force);
	void addTorque(Vec3 torque, Physics::ForceType forceType = Physics::ForceType::Force);

	ArkString toString() const override { return ArkString("Rigidbody"); }
	void copyFrom(Component const * component) override;
	ArkString getJson() const override;

private:
	Vec3 m_unresolvedForce;
	Physics::RigidbodyInfo * m_rigidbodyInfo;
};