#include "ArkRendering.h"
#include "ShaderLoader.h"
#include "ImageLoader.h"

ArkRendering::ShaderProgram::ShaderProgram(ArkString vertexShader, ArkString fragmentShader)
{
	mProgramId = LoadShaders(vertexShader.c_str(), fragmentShader.c_str());

	glGetProgramInterfaceiv(mProgramId, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &mNumAttributes);
	glGetProgramInterfaceiv(mProgramId, GL_UNIFORM, GL_ACTIVE_RESOURCES, &mNumUniforms);

	// TODO (AD) code to get more info http://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shade
}

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

void ArkRendering::MaterialInfo::getUniformLocationsFromShader(GLuint shaderProgramId)
{
	ambId = glGetUniformLocation(shaderProgramId, "material.ambient");
	difId = glGetUniformLocation(shaderProgramId, "material.diffuse");
	spcId = glGetUniformLocation(shaderProgramId, "material.specular");
	shiId = glGetUniformLocation(shaderProgramId, "material.shininess");
}

void ArkRendering::MaterialInfo::bindMaterialToShader() const
{
	glUniform3f(ambId, ambient.x, ambient.y, ambient.z);
	glUniform3f(difId, diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(spcId, specular.x, specular.y, specular.z);
	glUniform1f(shiId, shininess);
}
