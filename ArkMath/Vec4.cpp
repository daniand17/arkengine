#include <float.h>

#include "Vec4.h"

const Vec4 Vec4::one = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
const Vec4 Vec4::zero = Vec4(0.0f, 0.0f, 0.0f, 0.0f);

bool operator==(Vec4 const & lhs, Vec4 const & rhs)
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

bool operator!=(Vec4 const & lhs, Vec4 const & rhs)
{
	float xDel = lhs.x - rhs.x;
	float yDel = lhs.y - rhs.y;
	float zDel = lhs.z - rhs.z;
	float wDel = lhs.w - rhs.w;

	if ( xDel < 0 ) xDel = -xDel;
	if ( yDel < 0 ) yDel = -yDel;
	if ( zDel < 0 ) zDel = -zDel;
	if ( wDel < 0 ) wDel = -wDel;
	return !(xDel < FLT_EPSILON && yDel < FLT_EPSILON && zDel < FLT_EPSILON && wDel < FLT_EPSILON);
}

float & Vec4::operator[](unsigned short i)
{
	switch ( i )
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	}
	return x;
}

float const & Vec4::operator[](unsigned short i) const
{
	switch ( i )
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	}
	return x;
}
