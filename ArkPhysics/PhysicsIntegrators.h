#pragma once;

#include "ArkMath.h"
#include "Time.h"
#include "Physics.h"
#include "Rigidbody.h"

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
		//Derivative() : dx(Vec3::zero), dv(Vec3::zero) {}
	};

	// Taken from http://gafferongames.com/game-physics/integration-basics/
	class Rk4Integrator
	{
	public:
		void integrate(Rigidbody & rigidbody, float t, float dt)
		{
			Derivative a, b, c, d;

			// TODO Eventually do momentum from force instead of acceleration and velocity

			a = evaluate(rigidbody, t, 0.0f, Derivative());
			b = evaluate(rigidbody, t, dt * 0.5f, a);
			c = evaluate(rigidbody, t, dt * 0.5f, b);
			d = evaluate(rigidbody, t, dt, c);

			Vec3 dxdt = 1.0f / 6.0f * (a.vel + 2.0f * (b.vel + c.vel) + d.vel);
			Vec3 dvdt = 1.0f / 6.0f * (a.accel + 2.0f * (b.accel + c.accel) + d.accel);

			rigidbody.position = rigidbody.position + dxdt * dt;
			rigidbody.velocity = rigidbody.velocity + dvdt * dt;
		}

	private:
		Derivative evaluate(Rigidbody const & rigidbody, float t, float dt, Derivative const &d)
		{
			State state;
			state.pos = rigidbody.position + d.vel * dt;
			state.vel = rigidbody.velocity + d.accel * dt;

			Derivative output;
			output.vel = state.vel;
			output.accel = acceleration(state, rigidbody, dt); // maybe t + dt?

			return output;
		}

		// Returns the acceleration at this time
		Vec3 acceleration(State const & state, Rigidbody const & rigidbody, float t)
		{
			
			// TODO Eventually unresolved force may go here?
			// Need to factor in mass somehow
			// Need to be able to calculate all acceleration forces from here
			// TODO Eventually gravity may go here? 
			return Vec3::zero;
		}
	};
};
