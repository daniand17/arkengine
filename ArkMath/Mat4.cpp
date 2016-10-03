#include "Mat4.h"

#include <float.h>

Mat4::Mat4(glm::mat4 const & mat)
{
	mMat = mat;
}

void Mat4::operator*=(Mat4 const & matrix)
{
	mMat *= matrix.mMat;
}

Mat4 Mat4::operator-()
{
	return -mMat;
}

Mat4 Mat4::transpose() const
{
	return glm::transpose(mMat);
}

Mat4 operator+(Mat4 const & lhs, Mat4 const & rhs)
{
	return lhs.data() + rhs.data();
}

Mat4 operator-(Mat4 const & lhs, Mat4 const & rhs)
{
	return lhs.data() - rhs.data();
}

Mat4 operator*(Mat4 const & lhs, Mat4 const & rhs)
{
	return lhs.data() * rhs.data();
}

Mat4 operator*(Mat4 const & lhs, float scalar)
{
	return lhs.data() * scalar;
}

Mat4 operator*(float scalar, Mat4 const & lhs)
{
	return scalar * lhs.data();
}

Mat4 operator/(Mat4 const & lhs, float scalar)
{
	return lhs.data() / scalar;
}

bool operator==(Mat4 const & lhs, Mat4 const & rhs)
{
	return lhs.data() == rhs.data();
}

bool operator!=(Mat4 const & lhs, Mat4 const & rhs)
{
	return lhs.data() != rhs.data();
}

Mat4 Mat4::inverse() const
{
	return glm::inverse(mMat);
}