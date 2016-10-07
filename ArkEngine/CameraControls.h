#pragma once

#include "Vec3.h"

class CameraControls
{
private:
	Vec3 position;
	float speed;
	float mouseSpeed;
	float initialFOV;
	float verticalAngle;
	float horizontalAngle;
};