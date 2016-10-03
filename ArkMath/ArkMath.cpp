#include "ArkMath.h"

#include <glm\gtc\matrix_transform.hpp>
Vec4 ArkMath::operator*(Mat4 const & matrix, Vec4 const & vec4)
{

	Vec4 vec;
	/*vec.x = matrix[0] * vec4.x
		+ matrix[1] * vec4.y
		+ matrix[2] * vec4.z
		+ matrix[3] * vec4.w;

	vec.y = matrix[4] * vec4.x
		+ matrix[5] * vec4.y
		+ matrix[6] * vec4.z
		+ matrix[7] * vec4.w;

	vec.z = matrix[8] * vec4.x
		+ matrix[9] * vec4.y
		+ matrix[10] * vec4.z
		+ matrix[11] * vec4.w;

	vec.w = matrix[12] * vec4.x
		+ matrix[13] * vec4.y
		+ matrix[14] * vec4.z
		+ matrix[15] * vec4.w;*/

	return vec;
}

Mat4 ArkMath::perspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	return Mat4(glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane));
}

Mat4 ArkMath::orthographic()
{
	return Mat4();
}

Mat4 ArkMath::lookAt(Vec3 eye, Vec3 target, Vec3 upAxis)
{
	/*Vec3 zAxis = (eye - target).normalized();
	Vec3 xAxis = Vec3::cross(upAxis, zAxis).normalized();
	Vec3 yAxis = Vec3::cross(zAxis, xAxis);

	float a = -Vec3::dot(xAxis, eye);
	float b = -Vec3::dot(yAxis, eye);
	float c = -Vec3::dot(zAxis, eye);

	float viewMatrix[16] = {
		xAxis.x,	yAxis.x,	zAxis.x,	0,
		xAxis.y,	yAxis.y,	zAxis.y,	0,
		xAxis.z,	yAxis.z,	zAxis.z,	0,
		a,			b,			c,			1
	};*/

	return Mat4(glm::lookAt(glm::vec3(eye.x, eye.y, eye.z), glm::vec3(target.x, target.y, target.z), glm::vec3(upAxis.x, upAxis.y, upAxis.z)));
}
