#pragma once;

#include "ArkMath.h"
#include "Time.h"
#include "Physics.h"

using namespace Physics;

namespace Physics::Integrators
{
	struct State
	{
		Vec3 pos = Vec3::zero;
		Vec3 vel = Vec3::zero;
	};

	struct Derivative
	{
		Vec3 vel;
		Vec3 accel;
	};

	// Taken from http://gafferongames.com/game-physics/integration-basics/
	class Rk4Integrator
	{
	public:
		void integrate(RigidbodyInfo & rigidbody, float t, float dt);

	private:
		Derivative evaluate(RigidbodyInfo const & rigidbody, float t, float dt, Derivative const &d);
		// Returns the acceleration at this time
		Vec3 acceleration(State const & state, RigidbodyInfo const & rigidbody, float t);
	};
};
