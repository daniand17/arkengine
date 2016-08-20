#include "Mat4.h"

#include <float.h>

void Mat4::operator*=(Mat4 const & matrix)
{
	float mat[16];
	int row = 0;
	for ( int i = 0 ; i < 16 ; i++ )
	{
		int col = i % 4;
		if ( i != 0 && col == 0 ) row++;
		mat[i] = mElements[row * 4] * matrix.mElements[col] +
			mElements[row * 4 + 1] * matrix.mElements[col + 4] +
			mElements[row * 4 + 2] * matrix.mElements[col + 8] +
			mElements[row * 4 + 3] * matrix.mElements[col + 12];
	}

	for ( int i = 0 ; i < 16 ; i++ )
		mElements[i] = mat[i];
}

float & Mat4::operator[](unsigned short index)
{
	if ( index < 16 )
		return mElements[index];
	else
		return mElements[0];
}

Mat4 Mat4::operator-()
{
	Mat4 mat;
	for ( unsigned short i = 0 ; i < 16 ; i++ )
		mat.mElements[i] = -mElements[i];
	return mat;
}

Mat4 Mat4::transpose() const
{
	Mat4 mat;
	mat.mElements[0] = mElements[0];
	mat.mElements[1] = mElements[4];
	mat.mElements[2] = mElements[8];
	mat.mElements[3] = mElements[12];
	mat.mElements[4] = mElements[1];
	mat.mElements[5] = mElements[5];
	mat.mElements[6] = mElements[8];
	mat.mElements[7] = mElements[13];
	mat.mElements[8] = mElements[2];
	mat.mElements[9] = mElements[6];
	mat.mElements[10] = mElements[10];
	mat.mElements[11] = mElements[14];
	mat.mElements[12] = mElements[3];
	mat.mElements[13] = mElements[7];
	mat.mElements[14] = mElements[11];
	mat.mElements[15] = mElements[15];
	return mat;
}

Mat4 operator+(Mat4 const & lhs, Mat4 const & rhs)
{
	Mat4 mat;
	for ( unsigned short i = 0 ; i < 16 ; i++ )
		mat[i] = lhs[i] + rhs[i];
	return mat;
}

Mat4 operator-(Mat4 const & lhs, Mat4 const & rhs)
{
	Mat4 mat;
	for ( unsigned short i = 0 ; i < 16 ; i++ )
		mat[i] = lhs[i] - rhs[i];
	return mat;
}

Mat4 operator*(Mat4 const & lhs, Mat4 const & rhs)
{
	Mat4 mat;
	int row = 0;
	for ( int i = 0 ; i < 16 ; i++ )
	{
		int col = i % 4;
		if ( i != 0 && col == 0 ) row++;
		int rowInd = row * 4;
		mat[i] = lhs[rowInd] * rhs[col]
			+ lhs[rowInd + 1] * rhs[col + 4]
			+ lhs[rowInd + 2] * rhs[col + 8]
			+ lhs[rowInd + 3] * rhs[col + 12];
	}
	return mat;
}

Mat4 operator*(Mat4 const & lhs, float scalar)
{
	Mat4 mat;
	for ( unsigned short i = 0 ; i < 16 ; i++ )
		mat[i] = lhs[i] * scalar;
	return mat;
}

Mat4 operator*(float scalar, Mat4 const & lhs)
{
	Mat4 mat;
	for ( unsigned short i = 0 ; i < 16 ; i++ )
		mat[i] = lhs[i] * scalar;
	return mat;
}

Mat4 operator/(Mat4 const & lhs, float scalar)
{
	Mat4 mat;
	for ( unsigned short i = 0 ; i < 16 ; i++ )
		mat[i] = lhs[i] / scalar;
	return mat;
}

bool operator==(Mat4 const & lhs, Mat4 const & rhs)
{
	for ( unsigned short i = 0 ; i < 16 ; i++ )
	{
		float val = lhs[i] - rhs[i];
		if ( val < 0 ) val = -val;
		if ( val > FLT_EPSILON ) return false;
	}

	return true;
}

bool operator!=(Mat4 const & lhs, Mat4 const & rhs)
{
	for ( unsigned short i = 0 ; i < 16 ; i++ )
	{
		float val = lhs[i] - rhs[i];
		if ( val < 0 ) val = -val;
		if ( val > FLT_EPSILON ) return true;
	}

	return false;
}

Mat4 Mat4::inverse() const
{
	Mat4 inv;

	inv.mElements[0] = mElements[5] * mElements[10] * mElements[15] -
		mElements[5] * mElements[11] * mElements[14] -
		mElements[9] * mElements[6] * mElements[15] +
		mElements[9] * mElements[7] * mElements[14] +
		mElements[13] * mElements[6] * mElements[11] -
		mElements[13] * mElements[7] * mElements[10];

	inv.mElements[1] = -mElements[1] * mElements[10] * mElements[15] +
		mElements[1] * mElements[11] * mElements[14] +
		mElements[9] * mElements[2] * mElements[15] -
		mElements[9] * mElements[3] * mElements[14] -
		mElements[13] * mElements[2] * mElements[11] +
		mElements[13] * mElements[3] * mElements[10];

	inv.mElements[2] = mElements[1] * mElements[6] * mElements[15] -
		mElements[1] * mElements[7] * mElements[14] -
		mElements[5] * mElements[2] * mElements[15] +
		mElements[5] * mElements[3] * mElements[14] +
		mElements[13] * mElements[2] * mElements[7] -
		mElements[13] * mElements[3] * mElements[6];

	inv.mElements[3] = -mElements[1] * mElements[6] * mElements[11] +
		mElements[1] * mElements[7] * mElements[10] +
		mElements[5] * mElements[2] * mElements[11] -
		mElements[5] * mElements[3] * mElements[10] -
		mElements[9] * mElements[2] * mElements[7] +
		mElements[9] * mElements[3] * mElements[6];

	inv.mElements[4] = -mElements[4] * mElements[10] * mElements[15] +
		mElements[4] * mElements[11] * mElements[14] +
		mElements[8] * mElements[6] * mElements[15] -
		mElements[8] * mElements[7] * mElements[14] -
		mElements[12] * mElements[6] * mElements[11] +
		mElements[12] * mElements[7] * mElements[10];

	inv.mElements[5] = mElements[0] * mElements[10] * mElements[15] -
		mElements[0] * mElements[11] * mElements[14] -
		mElements[8] * mElements[2] * mElements[15] +
		mElements[8] * mElements[3] * mElements[14] +
		mElements[12] * mElements[2] * mElements[11] -
		mElements[12] * mElements[3] * mElements[10];

	inv.mElements[6] = -mElements[0] * mElements[6] * mElements[15] +
		mElements[0] * mElements[7] * mElements[14] +
		mElements[4] * mElements[2] * mElements[15] -
		mElements[4] * mElements[3] * mElements[14] -
		mElements[12] * mElements[2] * mElements[7] +
		mElements[12] * mElements[3] * mElements[6];

	inv.mElements[7] = mElements[0] * mElements[6] * mElements[11] -
		mElements[0] * mElements[7] * mElements[10] -
		mElements[4] * mElements[2] * mElements[11] +
		mElements[4] * mElements[3] * mElements[10] +
		mElements[8] * mElements[2] * mElements[7] -
		mElements[8] * mElements[3] * mElements[6];

	inv.mElements[8] = mElements[4] * mElements[9] * mElements[15] -
		mElements[4] * mElements[11] * mElements[13] -
		mElements[8] * mElements[5] * mElements[15] +
		mElements[8] * mElements[7] * mElements[13] +
		mElements[12] * mElements[5] * mElements[11] -
		mElements[12] * mElements[7] * mElements[9];

	inv.mElements[9] = -mElements[0] * mElements[9] * mElements[15] +
		mElements[0] * mElements[11] * mElements[13] +
		mElements[8] * mElements[1] * mElements[15] -
		mElements[8] * mElements[3] * mElements[13] -
		mElements[12] * mElements[1] * mElements[11] +
		mElements[12] * mElements[3] * mElements[9];

	inv.mElements[10] = mElements[0] * mElements[5] * mElements[15] -
		mElements[0] * mElements[7] * mElements[13] -
		mElements[4] * mElements[1] * mElements[15] +
		mElements[4] * mElements[3] * mElements[13] +
		mElements[12] * mElements[1] * mElements[7] -
		mElements[12] * mElements[3] * mElements[5];

	inv.mElements[11] = -mElements[0] * mElements[5] * mElements[11] +
		mElements[0] * mElements[7] * mElements[9] +
		mElements[4] * mElements[1] * mElements[11] -
		mElements[4] * mElements[3] * mElements[9] -
		mElements[8] * mElements[1] * mElements[7] +
		mElements[8] * mElements[3] * mElements[5];

	inv.mElements[12] = -mElements[4] * mElements[9] * mElements[14] +
		mElements[4] * mElements[10] * mElements[13] +
		mElements[8] * mElements[5] * mElements[14] -
		mElements[8] * mElements[6] * mElements[13] -
		mElements[12] * mElements[5] * mElements[10] +
		mElements[12] * mElements[6] * mElements[9];

	inv.mElements[13] = mElements[0] * mElements[9] * mElements[14] -
		mElements[0] * mElements[10] * mElements[13] -
		mElements[8] * mElements[1] * mElements[14] +
		mElements[8] * mElements[2] * mElements[13] +
		mElements[12] * mElements[1] * mElements[10] -
		mElements[12] * mElements[2] * mElements[9];

	inv.mElements[14] = -mElements[0] * mElements[5] * mElements[14] +
		mElements[0] * mElements[6] * mElements[13] +
		mElements[4] * mElements[1] * mElements[14] -
		mElements[4] * mElements[2] * mElements[13] -
		mElements[12] * mElements[1] * mElements[6] +
		mElements[12] * mElements[2] * mElements[5];

	inv.mElements[15] = mElements[0] * mElements[5] * mElements[10] -
		mElements[0] * mElements[6] * mElements[9] -
		mElements[4] * mElements[1] * mElements[10] +
		mElements[4] * mElements[2] * mElements[9] +
		mElements[8] * mElements[1] * mElements[6] -
		mElements[8] * mElements[2] * mElements[5];

	float det = mElements[0] * inv.mElements[0] + mElements[1] * inv.mElements[4] + mElements[2] * inv.mElements[8] + mElements[3] * inv.mElements[12];
	if ( det == 0 )
		return Mat4();
	det = 1.0f / det;
	return inv * det;
}