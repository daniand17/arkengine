#include "stdafx.h"
#include "CppUnitTest.h"

#include "PhysicsIntegrators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Integrators;

namespace Test_ArkPhysics
{
	TEST_CLASS(PhysicsIntegrator_Test)
	{

		Rk4Integrator rk4;

		TEST_METHOD(Constructors)
		{
			State s;
			Assert::IsTrue(s.v == Vec3::zero);
			Assert::IsTrue(s.x == Vec3::zero);

			Derivative d;
			Assert::IsTrue(d.dv == Vec3::zero);
			Assert::IsTrue(d.dx == Vec3::zero);
		}

		TEST_METHOD(Initial_Velocity)
		{
			// An initial state with a velocity of (1, 1, 1) and a position of (0, 0, 0)
			State s;
			s.v = Vec3::one;
			s.x = Vec3::zero;

			rk4.integrate(s, 0.0f, 1.0f);

			Assert::IsTrue(s.x == Vec3::one);
		}
	};
}