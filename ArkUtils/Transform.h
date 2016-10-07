#pragma once
#include "Vec3.h"
#include "Quaternion.h"

class Transform
{
public:
	Transform();

private:
	Vec3 mPosition;
	Quaternion mRotation;
};