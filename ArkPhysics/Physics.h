#pragma once
#include "Vec3.h"
#include "Quaternion.h"

namespace Physics
{
	enum ForceType
	{
		Force,			// mass * distance / time ^ 2 (over time)
		Acceleration,	// distance / time ^ 2	(instantly)
		Impulse,		// mass * distance / time
		VelocityChange	// Distance / Time
	};

	Vec3 const gravity = Vec3(0.0f, 9.81f, 0.0f);

	struct RigidbodyInfo
	{
		Vec3 position;
		Quaternion rotation;
		float mass;
		float drag;
		float angularDrag;
	};
};