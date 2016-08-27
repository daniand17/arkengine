#pragma once;

#include "ArkMath.h"
#include "Time.h"

namespace Integrators
{
	struct State
	{
		Vec3 x;
		Vec3 v;
		//State() : x(Vec3::zero), v(Vec3::zero) {}
	};

	struct Derivative
	{
		Vec3 dx;
		Vec3 dv;
		//Derivative() : dx(Vec3::zero), dv(Vec3::zero) {}
	};

	// Taken from http://gafferongames.com/game-physics/integration-basics/
	class Rk4Integrator
	{
	public:
		Derivative evaluate(State const & initial, float t, float dt, Derivative const &d)
		{
			State state;
			state.x = initial.x + d.dx * dt;
			state.v = initial.v + d.dv * dt;

			Derivative output;
			output.dx = state.v;
			output.dv = acceleration(state, t + dt);

			return output;
		}

		Vec3 acceleration(State const & state, float t)
		{
			float const k = 10.0f;
			float const b = 1.0f;
			return -k * state.x - b * state.v;
			// FIXME Assumes unit mass currently
		}

		void integrate(State & state, float t, float dt)
		{
			Derivative a, b, c, d;

			// TODO Eventually do momentum from force instead of acceleration and velocity

			a = evaluate(state, t, 0.0f, Derivative());
			b = evaluate(state, t, dt * 0.5f, a);
			c = evaluate(state, t, dt * 0.5f, b);
			d = evaluate(state, t, dt, c);

			Vec3 dxdt = 1.0f / 6.0f * (a.dx + 2.0f * (b.dx + c.dx) + d.dx);
			Vec3 dvdt = 1.0f / 6.0f * (a.dv + 2.0f * (b.dv + c.dv) + d.dv);

			state.x = state.x + dxdt * dt;
			state.v = state.v + dvdt * dt;
		}
	};
};
