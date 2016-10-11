#pragma once
#include "Physics.h"
#include "ArkMath.h"

class Rk4Integrator
{

public:
	void integrate(Physics::RigidbodyInfo rigidbodyInfo, float time, float dt);

private:
	struct State
	{
		Vec3 position;
		Vec3 velocity;
	};

	struct Derivative
	{
		Vec3 velocity;
		Vec3 acceleration;
	};

	Derivative evaluate(State const & initial, float t, float dt, Derivative const & d);
};