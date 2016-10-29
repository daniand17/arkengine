#pragma once
#include "Vec3.h"
#include "Quaternion.h"
class GameObject
{
public:
	void instantiate(GameObject obj, Vec3 position, Quaternion rotation);

private:
};