#include "ArkRendering.h"
#include "ShaderLoader.h"
#include "ImageLoader.h"

ArkRendering::Texture::Texture(ArkString filename)
	: mTextureId(0)
{
	mTextureId = loadBMP_custom(filename.c_str());
}

void ArkRendering::LightInfo::bindLightToShader() const
{
	glUniform3f(eyeId, eyePosition.x, eyePosition.y, eyePosition.z);
	glUniform3f(colId, color.x, color.y, color.z);
}

void ArkRendering::LightInfo::getUniformLocationsFromShader(GLuint shaderProgramId)
{
	eyeId = glGetUniformLocation(shaderProgramId, "lightInfo.eyePosition");
	colId = glGetUniformLocation(shaderProgramId, "lightInfo.color");
}

void ArkRendering::MaterialInfo::setShaderProgram(GLuint shaderProgram)
{
	mShaderProgram = shaderProgram;
	glUseProgram(shaderProgram);
	ambId = glGetUniformLocation(shaderProgram, "material.ambient");
	difId = glGetUniformLocation(shaderProgram, "material.diffuse");
	spcId = glGetUniformLocation(shaderProgram, "material.specular");
	shiId = glGetUniformLocation(shaderProgram, "material.shininess");
}

void ArkRendering::MaterialInfo::UseShaderProgram() const
{
	glUseProgram(mShaderProgram);
	glUniform3f(ambId, ambient.x, ambient.y, ambient.z);
	glUniform3f(difId, diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(spcId, specular.x, specular.y, specular.z);
	glUniform1f(shiId, shininess);
}

ArkRendering::ShaderProgram::ShaderProgram(ArkString vertexShader, ArkString fragmentShader)
{
	mProgramId = LoadShaders(vertexShader.c_str(), fragmentShader.c_str());

	glGetProgramInterfaceiv(mProgramId, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &mNumAttributes);
	glGetProgramInterfaceiv(mProgramId, GL_UNIFORM, GL_ACTIVE_RESOURCES, &mNumUniforms);

	// TODO (AD) code to get more info http://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shade
}