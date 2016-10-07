#pragma once
#include "Component.h"

class Light	: public Component
{
public:
	enum LightType
	{
		Point,
		Directional,
		Spot
	};

private:
	LightType mType;
	Vec3 mColor;
	float mIntensity;
};