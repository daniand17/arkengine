#include <float.h>

#include "Vec3.h"

bool operator==(Vec3 const & lhs, Vec3 const & rhs)
{
	float xDel = lhs.x - rhs.x;
	float yDel = lhs.y - rhs.y;
	float zDel = lhs.z - rhs.z;

	if ( xDel < 0 ) xDel = -xDel;
	if ( yDel < 0 ) yDel = -yDel;
	if ( zDel < 0 ) zDel = -zDel;
	return xDel < FLT_EPSILON && yDel < FLT_EPSILON && zDel < FLT_EPSILON;
}

bool operator != (Vec3 const & lhs, Vec3 const & rhs)
{
	float xDel = lhs.x - rhs.x;
	float yDel = lhs.y - rhs.y;
	float zDel = lhs.z - rhs.z;

	if ( xDel < 0 ) xDel = -xDel;
	if ( yDel < 0 ) yDel = -yDel;
	if ( zDel < 0 ) zDel = -zDel;
	return !(xDel < FLT_EPSILON && yDel < FLT_EPSILON && zDel < FLT_EPSILON);
}

std::string Vec3::toString() const
{
	return std::string("Vec3(" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + ")");
}
