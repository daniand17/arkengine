#include "RenderPass.h"

RenderPass::RenderPass(ShaderProgram const * program)
{
	getVertexBindingsFromShader();
}



void RenderPass::useShaderProgramAndBindValues() const
{
	glUseProgram(m_program->getId());
	pushValuesToRenderer();
}



void RenderPass::pushValuesToRenderer() const
{
	//glUniform3f(ambId, ambient.x, ambient.y, ambient.z);
	//glUniform3f(difId, diffuse.x, diffuse.y, diffuse.z);
	//glUniform3f(spcId, specular.x, specular.y, specular.z);
	//glUniform1f(shiId, shininess);

}



void RenderPass::getVertexBindingsFromShader()
{
	if ( m_program != NULL )
	{
		GLuint shaderProgramId = m_program->getId();
		glUseProgram(shaderProgramId);
		//ambId = glGetUniformLocation(shaderProgramId, "material.ambient");
		//difId = glGetUniformLocation(shaderProgramId, "material.diffuse");
		//spcId = glGetUniformLocation(shaderProgramId, "material.specular");
		//shiId = glGetUniformLocation(shaderProgramId, "material.shininess");
	}
}