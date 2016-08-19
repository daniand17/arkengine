#include <string>
#include <math.h>
struct Vec3
{
	float x;
	float y;
	float z;

	Vec3() : x(0.0), y(0.0), z(0.0) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vec3(Vec3 & other) : x(other.x), y(other.y), z(other.z) {}

	void operator += (Vec3 const & other);
	void operator -= (Vec3 const & other);
	void operator *= (float scalar);
	void operator /= (float scalar);
	void operator = (Vec3 const & other);

	float dot(Vec3 const & other) const;
	Vec3 cross(Vec3 const & other) const;
	float magnitude() const { return std::sqrtf(sqrMagnitude()); }
	float sqrMagnitude() const { return x * x + y * y + z * z; }
	Vec3 normalized() const;

	static Vec3 cross(Vec3 const & lhs, Vec3 const & rhs);
	static float dot(Vec3 const & lhs, Vec3 const & rhs);
};

Vec3 operator + (Vec3 const & lhs, Vec3 const & rhs);
Vec3 operator - (Vec3 const & lhs, Vec3 const & rhs);
bool operator == (Vec3 const & lhs, Vec3 const & rhs);
Vec3 operator * (Vec3 const & vec, float scalar);
Vec3 operator * (float scalar, Vec3 const & vec);
Vec3 operator / (Vec3 const & vec, float scalar);
