#pragma once

#include "ShaderProgram.h"
#include "Vec3.h"

class RenderPass
{
public:
	RenderPass(ShaderProgram * program);
	RenderPass(ArkString passName, ArkString vertexShader, ArkString fragmentShader);

	void useShaderProgramAndBindValues() const;

	GLuint getShaderProgramId() const { return m_program->getId(); }

	Vec3 ambient;
	Vec3 diffuse;
	Vec3 specular;
	float shininess;

private:

	ShaderProgram * m_program;

	GLuint shiId;
	GLuint ambId;
	GLuint difId;
	GLuint spcId;

	void getVertexBindingsFromShader();
	void pushValuesToRenderer() const;
};