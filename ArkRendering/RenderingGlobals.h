#pragma once
#include "Vec3.h"

namespace RendererGlobals
{
	enum LightType
	{
		Point,
		Directional,
		Spot
	};

	struct LightInfo
	{
		LightType type;
		Vec3 worldPosition;
		Vec3 direction;
		Vec3 color;

		float lightPower;
	};

	struct MaterialInfo
	{
		float ka;
		float kd;
		float ks;
		float shininess;
	};
}