#pragma once
#include "Component.h"
#include "ArkRendering.h"

class Light	: public Component
{
public:
	

private:
	ArkRendering::LightType mType;
	Vec3 mColor;
	float mIntensity;
};