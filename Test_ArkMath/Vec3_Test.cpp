#include "stdafx.h"
#include "CppUnitTest.h"

#include "Vec3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test_ArkMath
{
	TEST_CLASS(Vec3_Test)
	{
	public:

		TEST_METHOD(Constructors)
		{
			Vec3 def;
			Assert::IsTrue(def == Vec3(0, 0, 0));
			Assert::IsFalse(def == Vec3(1, 1, 1));

			Vec3 vec(1, 1, 1);
			Vec3 vec1(2, 2, 2);

			// Copy constructor
			Vec3 cpy(vec1);
			Assert::IsTrue(cpy == vec1);
		}

		TEST_METHOD(Equality)
		{
			Vec3 def(1, 1, 1);

			Assert::IsTrue(def == Vec3(1, 1, 1));
			Assert::IsFalse(def != Vec3(1, 1, 1));
			// Eps check
			Assert::IsTrue(def != Vec3(1.0000001, 1.0000001, 1.0000001));
			Assert::IsTrue(def == Vec3(1.00000001, 1.00000001, 1.00000001));
		}

		TEST_METHOD(Addition)
		{
			Vec3 vec(1, 1, 1);
			Vec3 vec1(2, 2, 2);

			Assert::IsTrue(vec + vec1 == Vec3(3, 3, 3));

			vec += vec1;

			Assert::IsTrue(vec == Vec3(3, 3, 3));
		}

		TEST_METHOD(Subtraction)
		{
			Vec3 lhs(2, 2, 2);
			Vec3 rhs(4, 4, 4);

			Assert::IsTrue(rhs - lhs == lhs);
			rhs -= lhs;
			Assert::IsTrue(rhs == lhs);

		}

		TEST_METHOD(Negative)
		{
			Vec3 vec(1, 1, 1);
			vec = -vec;
			Assert::IsTrue(vec == Vec3(-1, -1, -1));
		}

		TEST_METHOD(Scaling_Multiplication)
		{
			Vec3 vec(2, 2, 2);
			vec *= 2;
			Assert::IsTrue(vec == Vec3(4, 4, 4));
			Assert::IsTrue(vec * 2 == Vec3(8, 8, 8));
			Assert::IsTrue(vec * 0.5 == Vec3(2, 2, 2));
			vec *= 0.5;
			Assert::IsTrue(vec == Vec3(2, 2, 2));
		}

		TEST_METHOD(Scaling_Division)
		{
			Vec3 vec(2, 2, 2);
			vec = vec / 2;
			Assert::IsTrue(vec == Vec3(1, 1, 1));

			Vec3 vec1(2, 2, 2);
			vec1 /= 2;
			Assert::IsTrue(vec == vec1);
		}

		TEST_METHOD(Assignment)
		{
			Vec3 vec;
			Vec3 other(3, 3, 3);

			Assert::IsFalse(vec == other);
			vec = other;
			Assert::IsTrue(vec == other);
		}

		TEST_METHOD(Dot)
		{
			Vec3 lhs(1, 2, 3);
			Vec3 rhs(3, 2, 1);

			Assert::IsTrue(lhs.dot(rhs) == 10.0f);

			Vec3 orth0(1, 0, 0);
			Vec3 orth1(0, 1, 0);

			Assert::IsTrue(orth0.dot(orth1) == 0);
			Assert::IsTrue(Vec3::dot(orth0, orth1) == 0);
			Assert::IsTrue(Vec3::dot(lhs, rhs) == 10.0f);

			Assert::IsTrue(lhs.dot(lhs) == lhs.sqrMagnitude());

		}

		TEST_METHOD(Cross)
		{
			Vec3 vecX(1, 0, 0);
			Vec3 vecY(0, 1, 0);
			Vec3 vecZ(0, 0, 1);

			Assert::IsTrue(vecX.cross(vecY) == vecZ);
			Assert::IsTrue(vecY.cross(vecZ) == vecX);

			Assert::IsTrue(Vec3::cross(vecX, vecY) == vecZ);
			Assert::IsTrue(Vec3::cross(vecY, vecZ) == vecX);

			Assert::IsTrue(Vec3::cross(vecY, vecX) == -vecZ);
			Assert::IsTrue(vecY.cross(vecX) == -vecZ);

		}

		TEST_METHOD(Normalization)
		{
			Vec3 vec(1, 0, 0);

			//vec = vec.normalized();

			Assert::IsTrue(vec == Vec3(1, 0, 0));

			Vec3 vec1(3, 3, 3);

			/*Assert::IsTrue(vec1.normalized() == vec1 / vec1.magnitude());
			Assert::IsFalse(vec1.normalized() == vec1 / vec1.sqrMagnitude());*/
		}

		TEST_METHOD(Magnitude)
		{
			Vec3 vec(1, 1, 1);
			float sqrMag = vec.sqrMagnitude();
			float mag = vec.magnitude();

			Assert::IsTrue(sqrMag == 3.0f);
			Assert::IsTrue(mag == sqrtf(sqrMag));
		}
	};
}