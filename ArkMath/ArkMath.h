#pragma once

#include "Mat4.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

namespace ArkMath
{
	Vec4 operator * (Mat4 const & matrix, Vec4 const & vec4);
};
