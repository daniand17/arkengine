#include "stdafx.h"
#include "CppUnitTest.h"

#include "Vec4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test_ArkMath
{
	TEST_CLASS(Vec4_Test)
	{
	public:

		TEST_METHOD(Constructors)
		{
			Vec4 def;
			Assert::IsTrue(def == Vec4(0, 0, 0, 0));
			Assert::IsFalse(def == Vec4(1, 1, 1, 1));

			Vec4 vec(1, 1, 1, 1);
			Vec4 vec1(2, 2, 2, 2);

			// Copy constructor
			Vec4 cpy(vec1);
			Assert::IsTrue(cpy == vec1);

		}

		TEST_METHOD(Const_Static_Vecs)
		{
			Assert::IsTrue(Vec4::one + Vec4::one == Vec4(2.0f, 2.0f, 2.0f, 2.0f));
			Assert::IsTrue(Vec4::one + Vec4::zero == Vec4::one);
		}

		TEST_METHOD(Equality)
		{
			Vec4 def(1, 1, 1, 1);

			Assert::IsTrue(def == Vec4(1, 1, 1, 1));
			Assert::IsFalse(def != Vec4(1, 1, 1, 1));
			// Eps check
			Assert::IsTrue(def != Vec4(1.0f + FLT_EPSILON, 1.0f + FLT_EPSILON, 1.0f + FLT_EPSILON, 1.0f + FLT_EPSILON));
			Assert::IsTrue(def == Vec4(1.000000001f, 1.000000001f, 1.000000001f, 1.00000001f));
		}

		TEST_METHOD(Addition)
		{
			Vec4 vec(1, 1, 1, 1);
			Vec4 vec1(2, 2, 2, 2);

			Assert::IsTrue(vec + vec1 == Vec4(3, 3, 3, 3));

			vec += vec1;

			Assert::IsTrue(vec == Vec4(3, 3, 3, 3));

			Assert::IsTrue(-Vec4(2, 2, 2, 2) + Vec4(4, 4, 4, 4) == Vec4(2, 2, 2, 2));
		}

		TEST_METHOD(Subtraction)
		{
			Vec4 lhs(2, 2, 2, 2);
			Vec4 rhs(4, 4, 4, 4);

			Assert::IsTrue(rhs - lhs == lhs);
			rhs -= lhs;
			Assert::IsTrue(rhs == lhs);

		}

		TEST_METHOD(Negative)
		{
			Vec4 vec(1, 1, 1, 1);
			vec = -vec;
			Assert::IsTrue(vec == Vec4(-1, -1, -1, -1));
		}

		TEST_METHOD(Scaling_Multiplication)
		{
			Vec4 vec(2, 2, 2, 2);
			vec *= 2;
			Assert::IsTrue(vec == Vec4(4, 4, 4, 4));
			Assert::IsTrue(vec * 2 == Vec4(8, 8, 8, 8));
			Assert::IsTrue(vec * 0.5 == Vec4(2, 2, 2, 2));
			vec *= 0.5;
			Assert::IsTrue(vec == Vec4(2, 2, 2, 2));
		}

		TEST_METHOD(Scaling_Division)
		{
			Vec4 vec(2, 2, 2, 2);
			vec = vec / 2;
			Assert::IsTrue(vec == Vec4(1, 1, 1, 1));

			Vec4 vec1(2, 2, 2, 2);
			vec1 /= 2;
			Assert::IsTrue(vec == vec1);
		}

		TEST_METHOD(Assignment)
		{
			Vec4 vec;
			Vec4 other(3, 3, 3, 3);

			Assert::IsFalse(vec == other);
			vec = other;
			Assert::IsTrue(vec == other);
		}

		TEST_METHOD(Dot)
		{
			Vec4 lhs(1, 2, 3, 4);
			Vec4 rhs(4, 3, 2, 1);

			Assert::IsTrue(lhs.dot(rhs) == 20.0f);

			Vec4 orth0(1, 0, 0, 0);
			Vec4 orth1(0, 1, 0, 0);

			Assert::IsTrue(orth0.dot(orth1) == 0);
			// statics
			Assert::IsTrue(Vec4::dot(orth0, orth1) == 0);
			Assert::IsTrue(Vec4::dot(lhs, rhs) == 20.0f);
			// Definition of dot product of a vector with itself is square magnitude
			Assert::IsTrue(lhs.dot(lhs) == lhs.sqrMagnitude());
		}

		TEST_METHOD(Normalization)
		{
			Vec4 vec(1, 0, 0, 0);

			//vec = vec.normalized();

			Assert::IsTrue(vec == Vec4(1, 0, 0, 0));

			Vec4 vec1(3, 3, 3, 3);

			/*Assert::IsTrue(vec1.normalized() == vec1 / vec1.magnitude());
			Assert::IsFalse(vec1.normalized() == vec1 / vec1.sqrMagnitude());*/
		}

		TEST_METHOD(Magnitude)
		{
			Vec4 vec(1, 1, 1, 1);
			float sqrMag = vec.sqrMagnitude();
			float mag = vec.magnitude();

			Assert::IsTrue(sqrMag == 4.0f);
			Assert::IsTrue(mag == sqrtf(sqrMag));
		}
	};
}