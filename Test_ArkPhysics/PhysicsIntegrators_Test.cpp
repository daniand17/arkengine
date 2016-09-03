#include "stdafx.h"
#include "CppUnitTest.h"

#include "Rigidbody.h"
#include "PhysicsIntegrators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Integrators;

namespace Test_ArkPhysics
{
	TEST_CLASS(PhysicsIntegrator_Test)
	{

		Integrators::Rk4Integrator rk4;

		TEST_METHOD(Constructors)
		{
			Rigidbody rb;
			Assert::IsTrue(rb.velocity == Vec3::zero);
			Assert::IsTrue(rb.position == Vec3::zero);

			Derivative d;
			Assert::IsTrue(d.accel == Vec3::zero);
			Assert::IsTrue(d.vel == Vec3::zero);
		}

		TEST_METHOD(Integrate_Unit_Velocity_No_Grav)
		{
			// An initial state with a velocity of (1, 1, 1) and a position of (0, 0, 0)
			Rigidbody rb;
			rb.gravityScale = 0.0f;
			rb.velocity = Vec3(1, 0, 0);
			rb.position = Vec3::zero;

			rk4.integrate(rb, 0.0f, 1.0f);

			Assert::IsTrue(rb.position == Vec3(1, 0, 0));

			rb.velocity = Vec3::one;
			rb.position = Vec3::zero;

			rk4.integrate(rb, 0.0f, 1.0f);
			Assert::IsTrue(rb.velocity == Vec3::one);	// Velocity shouldn't change yet
			Assert::IsTrue(rb.position == Vec3::one);

			rb.position = Vec3::zero;
			rk4.integrate(rb, 0.0f, 0.5f);
			Assert::IsTrue(rb.position == Vec3::one / 2);
		}

		TEST_METHOD(Integrate_Neg_Velocity_No_Grav)
		{
			Rigidbody rb;
			rb.gravityScale = 0.0f;
			rb.velocity = -Vec3::one;
			rb.position = Vec3::zero;

			rk4.integrate(rb, 0.0f, 1.0f);
			Assert::IsTrue(rb.position == -Vec3::one);

			rb.velocity = -rb.velocity;
			
			rk4.integrate(rb, 0.0f, 1.0f);
			Assert::IsTrue(rb.position == Vec3::zero);
		}

		TEST_METHOD(Integrate_Rigidbody_With_Gravity)
		{
			Rigidbody rb;
			float dt = 1.0f;
			rk4.integrate(rb, 0.0f, dt);
			//Vec3 finalPos = Vec3::zero + Vec3::zero * dt + 0.5 * Physics::gravity * dt * dt;

			//Assert::IsTrue(rb.position == finalPos);

		}
	};
}