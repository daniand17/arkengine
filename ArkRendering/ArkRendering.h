#pragma once
#include <vector>

#include "Vec2.h"
#include "Vec3.h"
#include "BuildOptions.h"
#include "ArkString.h"
#include "Mat4.h"
#include "ProjectResource.h"
#include "ShaderProgram.h"
#include "MaterialResource.h"

namespace ArkRendering
{
	struct CameraInfo
	{
		Mat4 projectionMatrix;
		Mat4 viewMatrix;
		Vec3 position;
	};

}