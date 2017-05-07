#pragma once
#include <vector>

#include "Vec2.h"
#include "Vec3.h"
#include "BuildOptions.h"
#include "ArkString.h"
#include "Mat4.h"
#include "Resource.h"
#include "ShaderProgram.h"
#include "MaterialInfo.h"

namespace ArkRendering
{
	struct CameraInfo
	{
		Mat4 projectionMatrix;
		Mat4 viewMatrix;
		Vec3 position;
	};

	struct LightInfo
	{
		enum LightType
		{
			Point,
			Directional,
			Spot
		};

		Vec3 eyePosition;
		Vec3 color;

		void bindLightToShader() const;
		void getUniformLocationsFromShader(GLuint shaderProgramId);

	private:
		GLuint eyeId;
		GLuint colId;
	};

	////////////////////////////////////////

	struct ModelInfo : Resource
	{
		ModelInfo()
			: m_material("")
			, m_mesh("")
			, modelMatrix(Mat4::identity())
		{
		}

		ArkString m_material;
		ArkString m_mesh;
		Mat4 modelMatrix;

		ArkString serialize() const override;
	};
}