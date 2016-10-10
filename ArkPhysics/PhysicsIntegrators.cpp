#include "PhysicsIntegrators.h"

using namespace Physics::Integrators;
void Rk4Integrator::integrate(RigidbodyInfo & rigidbody, float t, float dt)
{
	Derivative a, b, c, d;

	// TODO Eventually do momentum from force instead of acceleration and velocity

	a = evaluate(rigidbody, t, 0.0f, Derivative());
	b = evaluate(rigidbody, t, dt * 0.5f, a);
	c = evaluate(rigidbody, t, dt * 0.5f, b);
	d = evaluate(rigidbody, t, dt, c);

	Vec3 dxdt = 1.0f / 6.0f * (a.vel + 2.0f * (b.vel + c.vel) + d.vel);
	Vec3 dvdt = 1.0f / 6.0f * (a.accel + 2.0f * (b.accel + c.accel) + d.accel);

	/*rigidbody.position = rigidbody.position + dxdt * dt;
	rigidbody.velocity = rigidbody.velocity + dvdt * dt;*/
	// TODO Create a rigidbody info
}

Derivative Rk4Integrator::evaluate(RigidbodyInfo const & rigidbody, float t, float dt, Derivative const &d)
{
	State state;
	/*state.pos = rigidbody.position + d.vel * dt;
	state.vel = rigidbody.velocity + d.accel * dt;*/

	Derivative output;
	output.vel = state.vel;
	output.accel = acceleration(state, rigidbody, dt); // maybe t + dt?
	return output;
}

// Returns the acceleration at this time
Vec3 Rk4Integrator::acceleration(State const & state, RigidbodyInfo const & rigidbody, float t)
{
	Vec3 accel = /*rigidbody.mUnresolvedForce / rigidbody.mass + rigidbody.gravityScale * */Physics::gravity;
	// TODO Eventually unresolved force may go here?
	// Need to factor in mass somehow
	// Need to be able to calculate all acceleration forces from here
	// TODO Eventually gravity may go here? 
	return accel * t;
}
