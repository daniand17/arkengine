#pragma once
struct Quaternion
{
	Quaternion() : x(0), y(0), z(0), w(0) { }
	Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	float x, y, z, w;
};

bool operator == (Quaternion const & lhs, Quaternion const & rhs);