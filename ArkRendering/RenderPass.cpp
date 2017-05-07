#include "RenderPass.h"

RenderPass::RenderPass(ShaderProgram * program)
	: ambient(Vec3::one())
	, diffuse(Vec3::one())
	, specular(Vec3::one())
	, shininess(0.0f)
	, shiId(0)
	, ambId(0)
	, difId(0)
	, spcId(0)
{
	getVertexBindingsFromShader();

}

RenderPass::RenderPass(ArkString passName, ArkString vertexShader, ArkString fragmentShader)
{
	m_program = new ShaderProgram(passName, vertexShader, fragmentShader);
	m_program->compileAndLoadShader();

}

void RenderPass::useShaderProgramAndBindValues() const
{
	glUseProgram(m_program->getId());
	pushValuesToRenderer();
}



void RenderPass::pushValuesToRenderer() const
{
	glUniform3f(ambId, ambient.x, ambient.y, ambient.z);
	glUniform3f(difId, diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(spcId, specular.x, specular.y, specular.z);
	glUniform1f(shiId, shininess);

}



void RenderPass::getVertexBindingsFromShader()
{
	if ( m_program!= NULL )
	{
		GLuint shaderProgramId = m_program->getId();
		glUseProgram(shaderProgramId);
		ambId = glGetUniformLocation(shaderProgramId, "material.ambient");
		difId = glGetUniformLocation(shaderProgramId, "material.diffuse");
		spcId = glGetUniformLocation(shaderProgramId, "material.specular");
		shiId = glGetUniformLocation(shaderProgramId, "material.shininess");
	}
}