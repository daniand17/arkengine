#include "Vec3.h"

void Vec3::operator+=(Vec3 const &  other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vec3::operator-=(Vec3 const & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

void Vec3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

void Vec3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
}

void Vec3::operator=(Vec3 const & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

float Vec3::dot(Vec3 const & other) const
{
	return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(Vec3 const & other) const
{
	// TODO Method stub for Vec3::cross
	return Vec3();
}

Vec3 Vec3::normalized() const
{
	return Vec3(x, y, z) / magnitude();
}

Vec3 Vec3::cross(Vec3 const & lhs, Vec3 const & rhs)
{
	// TODO Method stub for Vec3::cross
	return Vec3();
}

float Vec3::dot(Vec3 const & lhs, Vec3 const & rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vec3 operator+(Vec3 const & lhs, Vec3 const & rhs)
{
	return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vec3 operator-(Vec3 const & lhs, Vec3 const & rhs)
{
	return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

bool operator==(Vec3 const & lhs, Vec3 const & rhs)
{
	float xDel = lhs.x - rhs.x;
	float yDel = lhs.y - rhs.y;
	float zDel = lhs.z - rhs.z;

	if ( xDel < 0 ) xDel = -xDel;
	if ( yDel < 0 ) yDel = -yDel;
	if ( zDel < 0 ) zDel = -zDel;

	return xDel + yDel + zDel < 0.0000001f;
}

Vec3 operator * (Vec3 const & vec, float scalar)
{
	return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}
Vec3 operator * (float scalar, Vec3 const & vec)
{
	return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

Vec3 operator/(Vec3 const & vec, float scalar)
{
	float val = 1 / scalar;
	return Vec3(vec.x * val, vec.y * val, vec.z * val);
}