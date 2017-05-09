#include <float.h>

#include "Quaternion.h"

bool operator == (Quaternion const & lhs, Quaternion const & rhs)
{
	float xDel = lhs.x - rhs.x;
	float yDel = lhs.y - rhs.y;
	float zDel = lhs.z - rhs.z;
	float wDel = lhs.w - rhs.w;

	if ( xDel < 0 ) xDel = -xDel;
	if ( yDel < 0 ) yDel = -yDel;
	if ( zDel < 0 ) zDel = -zDel;
	if ( wDel < 0 ) wDel = -wDel;
	return xDel < FLT_EPSILON && yDel < FLT_EPSILON && zDel < FLT_EPSILON && wDel < FLT_EPSILON;
}


std::string Quaternion::toString() const
{
	return "Quat::toString()";
}