#include "stdafx.h"
#include "CppUnitTest.h"

#include "Rigidbody.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Physics;
namespace Test_ArkPhysics
{
	TEST_CLASS(Rigidbody_Test)
	{

		TEST_METHOD(Constructor)
		{
			Rigidbody rigidbody;

			// Assert that these are always the init conditions for a rigidbody
			Assert::AreEqual(rigidbody.mass, 1.0f);
			Assert::AreEqual(rigidbody.drag, 1.0f);
			Assert::AreEqual(rigidbody.angularDrag, 1.0f);
			Assert::AreEqual(rigidbody.gravityScale, 1.0f);
			Assert::IsTrue(rigidbody.position == Vec3::zero);
			Assert::IsTrue(rigidbody.velocity == Vec3::zero);
			Assert::IsTrue(rigidbody.angularVelocity == Vec3::zero);
		}

		TEST_METHOD(SizeOf_Rigidbody_is_80_bytes) {

			Rigidbody rb;
			Assert::IsTrue(sizeof(rb) == 80);

		}
	};
}