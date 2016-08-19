#include <float.h>

#include "Vec2.h"

bool operator == (Vec2 const & lhs, Vec2 const & rhs)
{
	float xDel = lhs.x - rhs.x;
	float yDel = lhs.y - rhs.y;

	if ( xDel < 0 ) xDel = -xDel;
	if ( yDel < 0 ) yDel = -yDel;

	return xDel < FLT_EPSILON && yDel < FLT_EPSILON;
}

bool operator != (Vec2 const & lhs, Vec2 const & rhs)
{
	float xDel = lhs.x - rhs.x;
	float yDel = lhs.y - rhs.y;

	if ( xDel < 0 ) xDel = -xDel;
	if ( yDel < 0 ) yDel = -yDel;

	return !(xDel < FLT_EPSILON && yDel < FLT_EPSILON);
}