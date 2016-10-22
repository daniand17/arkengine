#include "stdafx.h"
#include "CppUnitTest.h"

#include "Mat4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define _TEST_ARRAY {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
#define _TEST_ARRAY_TRANS {0, 4, 8, 12, 1, 5, 8, 13, 2, 6, 10, 14, 3, 7, 11, 15}
#define _TEST_ARRAY1 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
#define _TEST_ARRAY2 {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
#define _TEST_ARRAY3 {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
#define _TRANSLATION {1, 0, 0, 3, 0, 1, 0, 5, 0, 0, 1, 6, 0, 0, 0, 1}
#define _TRANS_INV {1, 0, 0, -3, 0, 1, 0, -5, 0, 0, 1, -6, 0, 0, 0, 1 }
namespace Test_ArkMath
{
	TEST_CLASS(Mat4_Test)
	{
	public:

		float arr1[16] = _TEST_ARRAY1;
		float arr2[16] = _TEST_ARRAY2;
		float arr3[16] = _TEST_ARRAY3;

		TEST_METHOD(Constructor)
		{
		}

		TEST_METHOD(Equality)
		{
		}

		TEST_METHOD(Assignment)
		{
		}

		TEST_METHOD(Assignment_Plus)
		{
		}

		TEST_METHOD(Assignment_Minus)
		{
		}

		TEST_METHOD(Assignment_Multiply_Matrix)
		{
		}

		TEST_METHOD(Assignment_Multiply_Scalar)
		{
			
		}

		TEST_METHOD(Assignment_Divide_Scalar)
		{
			
		}

		TEST_METHOD(Negative)
		{
		}

		TEST_METHOD(Transpose)
		{
			// Transpose of identity is identity
		}

		TEST_METHOD(Inverse)
		{
			// Inverse of identity is identity
		}

		TEST_METHOD(Binary_Plus)
		{
		}

		TEST_METHOD(Binary_Minus)
		{
		}

		TEST_METHOD(Binary_Multiply)
		{
		}

		TEST_METHOD(Multiply_Scalar)
		{
		}

		TEST_METHOD(Divide_Scalar)
		{
		}
	};
}
