#pragma once
#include <math.h>

struct Vec2
{
	float x;
	float y;

	Vec2() : x(0), y(0) {}
	Vec2(float x, float y) : x(x), y(y) {}
	Vec2(Vec2 const & other) : x(other.x), y(other.y) {}

	void operator += (Vec2 & other) { x += other.x; y += other.y; }
	void operator -= (Vec2 & other) { x -= other.x; y -= other.y; }
	void operator *= (float scalar) { x *= scalar; y *= scalar; }
	void operator /= (float scalar) { x /= scalar; y /= scalar; }
	void operator =  (Vec2 const & other) { x = other.x; y = other.y; }

	float dot(Vec2 const & other) const { return x * other.x + y * other.y; }
	Vec2 cross(Vec2 const & other) const {}
	float magnitude() const { return sqrtf(x * x + y * y); }
	float sqrMagnitude() const { return x * x + y * y; }
	Vec2 normalized() const { float mag = magnitude(); return Vec2(x / mag, y / mag); }

	static float dot(Vec2 const & lhs, Vec2 const & rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }
	static const Vec2 zero;
	static const Vec2 one;
};

bool operator == (Vec2 const & lhs, Vec2 const & rhs);
bool operator != (Vec2 const & lhs, Vec2 const & rhs);
inline Vec2 operator + (Vec2 const & lhs, Vec2 const & rhs) { return Vec2(lhs.x + rhs.x, lhs.y + rhs.y); }
inline Vec2 operator - (Vec2 const & lhs, Vec2 const & rhs) { return Vec2(lhs.x - rhs.x, lhs.y - rhs.y); }
inline Vec2 operator * (Vec2 const & vec, float scalar) { return Vec2(vec.x * scalar, vec.y * scalar); }
inline Vec2 operator * (float scalar, Vec2 const & vec) { return Vec2(vec.x * scalar, vec.y * scalar); }
inline Vec2 operator / (Vec2 const & vec, float scalar) { return Vec2(vec.x / scalar, vec.y / scalar); }
inline Vec2 operator - (Vec2 const & vec) { return Vec2(-vec.x, -vec.y); }