#pragma once

#include "Mat4.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#define PI 3.14159265f
#define TO_RADIANS 0.01745329f
#define TO_DEGREES 57.29577958f

namespace ArkMath
{
	Vec4 operator * (Mat4 const & matrix, Vec4 const & vec4);

	Mat4 perspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	Mat4 orthographic();
	Mat4 lookAt(Vec3 cameraPosition, Vec3 target, Vec3 axis);

	inline float toRadians(float degrees) { return degrees * TO_RADIANS; }
	inline float toDegrees(float radians) { return radians * TO_DEGREES; }
};
