#pragma once

#include <math.h>

struct Vec4
{
	float x;
	float y;
	float z;
	float w;

	Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Vec4(Vec4 const & other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

	void operator += (Vec4 const & other) { x += other.x; y += other.y;	z += other.z; w += other.w; }
	void operator -= (Vec4 const & other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; }
	void operator *= (float scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; }
	void operator /= (float scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; }
	void operator = (Vec4 const & other) { x = other.x;	y = other.y; z = other.z; w = other.w; }
	float & operator [] (unsigned short i);
	float const & operator [] (unsigned short i) const;

	float dot(Vec4 const & other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }
	float magnitude() const { return sqrtf(sqrMagnitude()); }
	float sqrMagnitude() const { return x * x + y * y + z * z + w * w; }
	Vec4 normalized() const
	{
		float val = magnitude();
		return Vec4(x / val, y / val, z / val, w / val);
	}

	static float dot(Vec4 const & lhs, Vec4 const & rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w; }
	static const Vec4 one;
	static const Vec4 zero;
};

bool operator == (Vec4 const & lhs, Vec4 const & rhs);
bool operator != (Vec4 const & lhs, Vec4 const & rhs);
inline Vec4 operator + (Vec4 const & lhs, Vec4 const & rhs) { return Vec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
inline Vec4 operator - (Vec4 const & lhs, Vec4 const & rhs) { return Vec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
inline Vec4 operator * (Vec4 const & vec, float scalar) { return Vec4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar); }
inline Vec4 operator * (float scalar, Vec4 const & vec) { return Vec4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar); }
inline Vec4 operator / (Vec4 const & vec, float scalar) { float val = 1 / scalar;	return Vec4(vec.x * val, vec.y * val, vec.z * val, vec.w * val); }
inline Vec4 operator-(Vec4 const & vec) { return Vec4(-vec.x, -vec.y, -vec.z, -vec.w); }
