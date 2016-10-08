#pragma once
#include "Component.h"
#include "RenderingGlobals.h"

class Light	: public Component
{
public:
	

private:
	RendererGlobals::LightType mType;
	Vec3 mColor;
	float mIntensity;
};