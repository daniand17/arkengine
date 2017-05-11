#pragma once
#include "Vec3.h"
#include "BuildOptions.h"

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