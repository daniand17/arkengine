#include "stdafx.h"
#include "CppUnitTest.h"

#include "ArkMath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ArkMath;

namespace Test_ArkMath
{
	TEST_CLASS(Vec4_Mat4_Integration)
	{

		float transformArray[16] =
		{
			1, 0, 0, 1,
			0, 1, 0, 1,
			0, 0, 1, 1,
			0, 0, 0, 1
		};

		TEST_METHOD(Vec4_Creation)
		{

			Vec4 vec;
			Assert::IsTrue(vec == Vec4::zero);

			Vec4 vec1(vec);
			Assert::IsTrue(vec1 == vec);
		}

		TEST_METHOD(Mat4_Creation)
		{
			Mat4 mat(transformArray);

			(mat * Mat4::identity() == mat);

		}

		TEST_METHOD(Mat_Vec_Multiply)
		{
			Vec4 vec(Vec4::one);

			Mat4 mat(transformArray);

			Vec4 result = mat * vec;
			Assert::IsTrue(result == Vec4(2, 2, 2, 1));

			mat = mat.inverse();

			result = mat * result;
			Assert::IsTrue(result == vec);
		}
	};
}