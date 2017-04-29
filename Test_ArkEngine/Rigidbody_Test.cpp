#include "stdafx.h"
#include "CppUnitTest.h"

#include "Rigidbody.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define SIZE_T(exp) static_cast<unsigned int>(exp)
namespace Test_ArkEngine
{
	TEST_CLASS(Rigidbody_Test)
	{
		TEST_METHOD(Rigidbody_CreationDefault)
		{
			Rigidbody rb(NULL);

			Assert::AreEqual(1.0f, rb.mass);
			Assert::AreEqual(1.0f, rb.drag);
			Assert::AreEqual(1.0f, rb.angularDrag);

			Assert::AreEqual(1.0f, rb.gravityScale);
			Assert::IsTrue(Vec3(0, 0, 0) == rb.angularVelocity);

			Assert::IsNull(rb.getTransform());
		}

		TEST_METHOD(Rigidbody_Copy)
		{
			Rigidbody rb(NULL);

			rb.mass = 2;
			rb.drag = 2;
			rb.angularDrag = 2;
			rb.gravityScale = 2;

			rb.position = Vec3(2, 2, 2);
			rb.velocity = Vec3(2, 2, 2);
			rb.angularVelocity = Vec3(2, 2, 2);
			rb.rotation = Quaternion(2, 2, 2, 2);

			Rigidbody rb0(NULL);
			rb0.copyFrom(&rb);
			Assert::AreEqual(rb.mass, rb0.mass);
			Assert::AreEqual(rb.drag, rb0.drag);
			Assert::AreEqual(rb.angularDrag, rb0.angularDrag);
			Assert::AreEqual(rb.gravityScale, rb0.gravityScale);
			Assert::IsTrue(rb.velocity == rb0.velocity);
			Assert::IsTrue(rb.angularVelocity == rb0.angularVelocity);
			Assert::IsTrue(rb.rotation == rb0.rotation);
		}
	};
}
