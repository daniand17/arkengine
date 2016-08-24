#include "ArkMath.h"

Vec4 ArkMath::operator*(Mat4 const & matrix, Vec4 const & vec4)
{
	Vec4 vec;
	vec.x = matrix[0] * vec4.x
		+ matrix[1] *	vec4.y
		+ matrix[2] *	vec4.z
		+ matrix[3] *	vec4.w;

	vec.y = matrix[4] * vec4.x
		+ matrix[5] *	vec4.y
		+ matrix[6] *	vec4.z
		+ matrix[7] *	vec4.w;

	vec.z = matrix[8] * vec4.x
		+ matrix[9] *	vec4.y
		+ matrix[10] *	vec4.z
		+ matrix[11] *	vec4.w;

	vec.w = matrix[12] * vec4.x
		+ matrix[13] *	 vec4.y
		+ matrix[14] *	 vec4.z
		+ matrix[15] *	 vec4.w;

	return vec;
}