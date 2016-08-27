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

		float translation[16] = _TRANSLATION;
		float translation_inverse[16] = _TRANS_INV;

		float test[16] = _TEST_ARRAY;
		float testTranspose[16] = _TEST_ARRAY_TRANS;

		TEST_METHOD(Constructor)
		{
			Mat4 mat;
			mat[0] = 1.0f;
			mat[5] = 1.0f;
			mat[10] = 1.0f;
			mat[15] = 1.0f;

			Mat4 identity = Mat4::identity();
			Assert::IsTrue(mat == identity);

			Mat4 anotherMat(Mat4::identity());

			Assert::IsTrue(anotherMat == Mat4::identity());
		}

		TEST_METHOD(Equality)
		{
			Mat4 mat;
			Assert::IsTrue(mat != Mat4::identity());
			float arr[16] = _TEST_ARRAY;
			mat = arr;

			Mat4 mat1;
			mat1 = arr;
			Assert::IsTrue(mat == mat1);
			Assert::IsTrue(mat != Mat4::identity());
		}

		TEST_METHOD(Assignment)
		{
			Mat4 mat = Mat4::identity();
			Assert::IsTrue(mat == Mat4::identity());

			float arr[16] = _TEST_ARRAY;
			mat = arr;
			Assert::IsFalse(mat == Mat4::identity());
		}

		TEST_METHOD(Assignment_Plus)
		{
			Mat4 mat = arr1;
			Mat4 mat2 = arr2;
			Mat4 mat3 = arr3;

			mat += mat2;
			Assert::IsTrue(mat == mat3);
		}

		TEST_METHOD(Assignment_Minus)
		{
			Mat4 mat = arr1;
			Mat4 mat2 = arr2;
			Mat4 mat3 = arr3;

			mat3 -= mat2;

			Assert::IsTrue(mat3 == mat);
		}

		TEST_METHOD(Assignment_Multiply_Matrix)
		{
			Mat4 mat = arr3;
			mat *= Mat4::identity();

			Mat4 mat3 = arr3;
			Assert::IsTrue(mat == mat3);

			Mat4 testMat = arr2;
			testMat += testMat;
			
			Mat4 mat4 = arr1;
			mat4 *= mat4;

			Assert::IsTrue(mat4 == testMat);
		}

		TEST_METHOD(Assignment_Multiply_Scalar)
		{
			Mat4 mat = arr2;
			mat *= 0.5f;
			Mat4 mat1 = arr1;
			Assert::IsTrue(mat == mat1);
			Mat4 mat3 = arr3;

			mat *= 3;
			Assert::IsTrue(mat == mat3);
		}

		TEST_METHOD(Assignment_Divide_Scalar)
		{
			Mat4 mat2 = arr2;
			Mat4 mat1 = arr1;

			mat2 /= 2;
			Assert::IsTrue(mat1 == mat2);
			mat2 *= 2;
			mat1 /= 0.5;
			Assert::IsTrue(mat1 == mat2);
		}

		TEST_METHOD(Negative)
		{
			Mat4 mat(Mat4::identity());
			mat = -mat;
			Assert::IsTrue(mat[0] == -1.0f && mat[5] == -1.0f && mat[10] == -1.0f && mat[15] == -1.0f);
			Assert::IsTrue(mat != Mat4::identity());
			mat = -mat;
			Assert::IsTrue(mat == Mat4::identity());
		}

		TEST_METHOD(Transpose)
		{
			// Transpose of identity is identity
			Mat4 mat(Mat4::identity());
			mat = mat.transpose();
			Assert::IsTrue(mat == Mat4::identity());

			Mat4 matTrans = testTranspose;
			mat = test;
			mat = mat.transpose();
			Assert::IsTrue(mat == matTrans);
		}

		TEST_METHOD(Inverse)
		{
			// Inverse of identity is identity
			Mat4 mat(Mat4::identity());
			mat = mat.inverse();
			Assert::IsTrue(mat == Mat4::identity());

			Mat4 mat1 = translation;
			mat1 = mat1.inverse();


			Mat4 inv = translation_inverse;
			Assert::IsTrue(mat1 == inv);
			mat1 -= inv;
			mat1 += Mat4::identity();
			Assert::IsTrue(mat1 == Mat4::identity());

			Mat4 anotherMat = translation;
			Mat4 nonInv = translation;
			anotherMat = anotherMat.inverse();
			nonInv += anotherMat;
			nonInv /= 2;
			Assert::IsTrue(nonInv == Mat4::identity());
		}

		TEST_METHOD(Binary_Plus)
		{
			Mat4 mat(Mat4::identity());
			Mat4 anotherMat = mat + mat;
			
			Assert::IsTrue(mat * 2 == anotherMat);
			anotherMat = anotherMat + -mat;
			Assert::IsTrue(anotherMat == mat);

			Assert::IsTrue(Mat4(arr1) + Mat4(arr2) == Mat4(arr3));
		}

		TEST_METHOD(Binary_Minus)
		{
			Mat4 mat3(arr3);
			Mat4 mat2(arr2);
			Mat4 mat1(arr1);

			Assert::IsTrue(mat3 - mat1 == mat2);
			Assert::IsTrue(mat2 - -mat1 == mat3);
		}

		TEST_METHOD(Binary_Multiply)
		{
			Mat4 mat1(arr1);
			Mat4 mat2(arr2);
			Mat4 mat3(arr3);
			Mat4 id(Mat4::identity());

			Mat4 prod(mat1);
			prod *= mat2;
			Assert::IsTrue(mat1 * mat2 == prod);

			Mat4 transMat(translation);

			Mat4 testMat(testTranspose);
			Assert::IsTrue(transMat * testMat != testMat * transMat);
		}

		TEST_METHOD(Multiply_Scalar)
		{
			Mat4 mat2(arr2);
			Mat4 mat1(arr1);

			Assert::IsTrue(mat1 * 2 == mat2);
			Assert::IsTrue(2 * mat1 == mat2);
		}

		TEST_METHOD(Divide_Scalar)
		{
			Mat4 mat1(arr1);
			Mat4 mat2(arr2);
			Assert::IsTrue(mat1 / 0.5f == mat2);
			Assert::IsTrue(mat2 / 2 == mat1);
		}
	};
}
