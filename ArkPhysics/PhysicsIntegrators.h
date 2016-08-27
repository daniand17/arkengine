#pragma once;

#include "ArkMath.h"
#include "Time.h"
#include "Physics.h"

namespace Integrators
{
	struct State
	{
		Vec3 pos;
		Vec3 vel;
		//State() : x(Vec3::zero), v(Vec3::zero) {}
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
		void integrate(State & state, float t, float dt)
		{
			Derivative a, b, c, d;

			// TODO Eventually do momentum from force instead of acceleration and velocity

			a = evaluate(state, t, 0.0f, Derivative());
			b = evaluate(state, t, dt * 0.5f, a);
			c = evaluate(state, t, dt * 0.5f, b);
			d = evaluate(state, t, dt, c);

			Vec3 dxdt = 1.0f / 6.0f * (a.vel + 2.0f * (b.vel + c.vel) + d.vel);
			Vec3 dvdt = 1.0f / 6.0f * (a.accel + 2.0f * (b.accel + c.accel) + d.accel);

			state.pos = state.pos + dxdt * dt;
			state.vel = state.vel + dvdt * dt;
		}

	private:
		Derivative evaluate(State const & initial, float t, float dt, Derivative const &d)
		{
			State state;
			state.pos = initial.pos + d.vel * dt;
			state.vel = initial.vel + d.accel * dt;

			Derivative output;
			output.vel = state.vel;
			output.accel = acceleration(state, dt); // maybe t + dt?

			return output;
		}

		// Returns the acceleration at this time
		Vec3 acceleration(State const & state, float t)
		{
			// FIXME Assumes unit mass currently
			// TODO Eventually unresolved force may go here?
			// Need to be able to calculate all acceleration forces from here
			return Physics::gravity * t;
		}
	};
};
