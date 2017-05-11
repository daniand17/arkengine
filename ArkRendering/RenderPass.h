#pragma once

#include "ShaderProgram.h"
#include "Vec3.h"


#include <map>

class RenderPass
{
public:
	RenderPass(ShaderProgram const * program);

	void useShaderProgramAndBindValues() const;
	GLuint getShaderProgramId() const { return m_program->getId(); }

private:

	ShaderProgram const * m_program;

	void getVertexBindingsFromShader();
	void pushValuesToRenderer() const;
};