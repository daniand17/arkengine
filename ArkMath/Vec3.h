#pragma once

#include <math.h>

struct Vec3
{
	float x;
	float y;
	float z;

	Vec3() : x(0.0), y(0.0), z(0.0) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vec3(Vec3 & other) : x(other.x), y(other.y), z(other.z) {}

	void operator += (Vec3 const & other) { x += other.x; y += other.y;	z += other.z; }
	void operator -= (Vec3 const & other) { x -= other.x; y -= other.y; z -= other.z; }
	void operator *= (float scalar) { x *= scalar; y *= scalar; z *= scalar; }
	void operator /= (float scalar) { x /= scalar; y /= scalar; z /= scalar; }
	void operator = (Vec3 const & other) { x = other.x;	y = other.y; z = other.z; }

	float dot(Vec3 const & other) const { return x * other.x + y * other.y + z * other.z; }
	Vec3 cross(Vec3 const & other) const { return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }
	float magnitude() const { return sqrtf(sqrMagnitude()); }
	float sqrMagnitude() const { return x * x + y * y + z * z; }
	Vec3 normalized() const { float val = magnitude(); return Vec3(x / val, y / val, z / val); }

	static Vec3 cross(Vec3 const & lhs, Vec3 const & rhs) { return Vec3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x); }
	static float dot(Vec3 const & lhs, Vec3 const & rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
};

bool operator == (Vec3 const & lhs, Vec3 const & rhs);
bool operator != (Vec3 const & lhs, Vec3 const & rhs); 
inline Vec3 operator + (Vec3 const & lhs, Vec3 const & rhs) { return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }
inline Vec3 operator - (Vec3 const & lhs, Vec3 const & rhs) { return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }
inline Vec3 operator * (Vec3 const & vec, float scalar) { return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar); }
inline Vec3 operator * (float scalar, Vec3 const & vec) { return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar); }
inline Vec3 operator / (Vec3 const & vec, float scalar) { float val = 1 / scalar;	return Vec3(vec.x * val, vec.y * val, vec.z * val); }
inline Vec3 operator-(Vec3 const & vec) { return Vec3(-vec.x, -vec.y, -vec.z); }
