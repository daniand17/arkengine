#include "stdafx.h"
#include "CppUnitTest.h"

#include "Vec2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test_ArkMath
{
	TEST_CLASS(Vec2_Test)
	{

		TEST_METHOD(Constructor)
		{
			Vec2 vec;
		}

		TEST_METHOD(Assignment)
		{
		}

		TEST_METHOD(Addition)
		{
		}

		TEST_METHOD(Dot)
		{
		}

		TEST_METHOD(Magnitude)
		{
		}

		TEST_METHOD(Normalization)
		{
		}

		TEST_METHOD(Equality)
		{
			Vec2 vec(1, 1);

			Assert::IsTrue(vec == Vec2(1, 1));
			Assert::IsFalse(vec != Vec2(1, 1));
			Assert::IsFalse(vec == Vec2(2, 2));
			Assert::IsTrue(vec != Vec2(2, 2));

			Assert::IsTrue(vec != Vec2(1.000001, 1.000001));
			// Eps
			Assert::IsTrue(vec == Vec2(1.00000001, 1.00000001));
			Assert::IsTrue(vec == Vec2(1.000000001, 1.000000001));

		}

		TEST_METHOD(Scaling_Division)
		{
		}

		TEST_METHOD(Scaling_Multiplication)
		{
		}

		TEST_METHOD(Subtraction)
		{
		}



	};
}