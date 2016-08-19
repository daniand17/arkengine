#include <math.h>

struct Vec2
{
	float x;
	float y;

	Vec2() : x(0), y(0) {}
	Vec2(float x, float y) : x(x), y(y) {}

	void operator+=(Vec2 & other) {}
	void operator-=(Vec2 & other) {}
	void operator*=(float scalar) {}
	void operator/=(float scalar) {}
	void operator = (Vec2 const & other) {}

	float dot(Vec2 const & other) const {}
	Vec2 cross(Vec2 const & other) const {}
	float magnitude() const {}
	float sqrMagnitude() const {}
	Vec2 normalized() const {}

	static Vec2 dot(Vec2 const & lhs, Vec2 const & rhs) {}
};

bool operator == (Vec2 const & lhs, Vec2 const & rhs);
bool operator != (Vec2 const & lhs, Vec2 const & rhs);
inline Vec2 operator + (Vec2 const & lhs, Vec2 const & rhs){}
inline Vec2 operator - (Vec2 const & lhs, Vec2 const & rhs){}
inline Vec2 operator * (Vec2 const & lhs, float scalar){}
inline Vec2 operator * (float scalar, Vec2 const & rhs){}
inline Vec2 operator / (Vec2 const & vec, float scalar) {}
inline Vec2 operator - (Vec2 const & vec) {}