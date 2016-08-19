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

			Assert::IsTrue(vec == Vec2(0, 0));

			Vec2 vec1(1, 1);
			Assert::IsTrue(vec1 == Vec2(1, 1));
			// Copy constructor
			Vec2 vec2(vec1);
			Assert::IsTrue(vec2 == vec1);
		}

		TEST_METHOD(Assignment)
		{
			Vec2 vec1;

			Vec2 otherVec(5, 5);
			vec1 = otherVec;

			Assert::IsTrue(vec1 == Vec2(5, 5));

			Vec2 vec(2, 2);
			vec *= 2;
			vec /= 4;
			Assert::IsTrue(vec == Vec2(1, 1));
			vec += Vec2(3, 3);
			vec -= Vec2(2, 2);
			Assert::IsTrue(vec == Vec2(2, 2));
		}

		TEST_METHOD(Addition)
		{
			Vec2 vec(1, 1);
			Vec2 vec1(2, 2);
			Assert::IsTrue(vec + vec1 == Vec2(3, 3));
			vec += vec1;
			Assert::IsTrue(vec == Vec2(3, 3));
			Assert::IsTrue(-Vec2(2, 2) + Vec2(4, 4) == Vec2(2, 2));
		}

		TEST_METHOD(Dot)
		{
			Assert::IsTrue(Vec2(2, 2).dot(Vec2(2, 2)) == 8);
			Assert::IsTrue(Vec2::dot(Vec2(1, 1), Vec2(1, 1)) == 2);
		}

		TEST_METHOD(Equality)
		{
			Vec2 vec(1, 1);

			Assert::IsTrue(vec == Vec2(1, 1));
			Assert::IsFalse(vec != Vec2(1, 1));
			Assert::IsFalse(vec == Vec2(2, 2));
			Assert::IsTrue(vec != Vec2(2, 2));

			Assert::IsTrue(vec != Vec2(1.000001f, 1.000001f));
			// Eps
			Assert::IsTrue(vec == Vec2(1.00000001f, 1.00000001f));
			Assert::IsTrue(vec == Vec2(1.000000001f, 1.000000001f)); // can't eval at this accuracy
		}

		TEST_METHOD(Scaling_Division)
		{
			Assert::IsTrue(Vec2(4, 4) / 2 == Vec2(2, 2));
			Assert::IsTrue(Vec2(4, 4) / 0.5 == Vec2(8, 8));

			Assert::IsFalse(Vec2(4, 4) / 0.5 == Vec2(6, 6));
			Assert::IsFalse(Vec2(8, 8) / 2 == Vec2(6, 6));
		}

		TEST_METHOD(Scaling_Multiplication)
		{
			// LHS vec
			Assert::IsTrue(Vec2(4, 4) * 2 == Vec2(8, 8));
			Assert::IsTrue(Vec2(4, 4) * 0.5 == Vec2(2, 2));
			Assert::IsFalse(Vec2(4, 4) * 0.5 == Vec2(6, 6));
			Assert::IsFalse(Vec2(8, 8) * 2 == Vec2(6, 6));
			// RHS vec
			Assert::IsTrue(2 * Vec2(4, 4) == Vec2(8, 8));
			Assert::IsTrue(0.5 * Vec2(4, 4) == Vec2(2, 2));
			Assert::IsFalse(0.5 * Vec2(4, 4) == Vec2(6, 6));
			Assert::IsFalse(2 * Vec2(8, 8) == Vec2(6, 6));
		}

		TEST_METHOD(Subtraction)
		{
			Assert::IsTrue(Vec2(5, 5) - Vec2(2, 2) == Vec2(3, 3));
			Assert::IsTrue(Vec2(4, 4) - -Vec2(3, 3) == Vec2(7, 7));
		}

		TEST_METHOD(Negative)
		{
			Assert::IsTrue(-Vec2(4, 4) == Vec2(-4, -4));
			Assert::IsTrue(Vec2(4, 4) - -Vec2(4, 4) == Vec2(8, 8));
			Assert::IsTrue(Vec2(4, 4) + -Vec2(4, 4) == Vec2(0, 0));
		}

		TEST_METHOD(Magnitude)
		{
			Assert::IsTrue(Vec2(1, 0).magnitude() == 1.0f);
			Assert::IsTrue(Vec2(1, 1).sqrMagnitude() == 2.0f);
			Assert::IsTrue(Vec2(1, 1).magnitude() == sqrt(2.0f));
			Assert::IsTrue(Vec2::dot(Vec2(2, 2), Vec2(2, 2)) == Vec2(2, 2).sqrMagnitude());
		}

		TEST_METHOD(Normalization)
		{
			Assert::IsTrue(Vec2(1, 0).normalized() == Vec2(1, 0));


		}
	};
}