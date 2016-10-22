#include <float.h>

#include "Vec2.h"
#include <sstream>
const Vec2 Vec2::zero(0.0f, 0.0f);
const Vec2 Vec2::one(1.0f, 1.0f);

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

std::string Vec2::ToString() const
{
	return std::string("Vec2(" + std::to_string(x) + " " + std::to_string(y) + ")");
}
