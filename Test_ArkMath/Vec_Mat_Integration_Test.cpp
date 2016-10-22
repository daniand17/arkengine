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
		}

		TEST_METHOD(Mat_Vec_Multiply)
		{
			Vec4 vec(Vec4::one);




		}
	};
}