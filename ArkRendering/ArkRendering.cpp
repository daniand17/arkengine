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



void ArkRendering::MaterialInfo::setShaderProgram(GLuint shaderProgram, bool bind)
{
	mShaderProgram = shaderProgram;
	if(bind)
	{
		glUseProgram(shaderProgram);
		ambId = glGetUniformLocation(shaderProgram, "material.ambient");
		difId = glGetUniformLocation(shaderProgram, "material.diffuse");
		spcId = glGetUniformLocation(shaderProgram, "material.specular");
		shiId = glGetUniformLocation(shaderProgram, "material.shininess");
	}
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
	m_vertexShader = vertexShader;
	m_fragmentShader = fragmentShader;
	mProgramId = LoadShaders(vertexShader.c_str(), fragmentShader.c_str());

	glGetProgramInterfaceiv(mProgramId, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &mNumAttributes);
	glGetProgramInterfaceiv(mProgramId, GL_UNIFORM, GL_ACTIVE_RESOURCES, &mNumUniforms);

	// TODO (AD) code to get more info http://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shade
}


ArkString ArkRendering::ShaderProgram::Synchronize() const
{
	ArkString sync("ShaderProgram");
	sync += "\tid:" + ArkString::Number(id);
	sync += "\tvertexShader:" + m_vertexShader;
	sync += "\n\tfragmentShader:" + m_fragmentShader;
	return sync;
}


ArkString ArkRendering::MeshInfo::Synchronize() const
{
	ArkString syncString = "MeshInfo";
	syncString += "\n\tname:" + name;
	return syncString;
}


ArkString ArkRendering::ModelInfo::Synchronize() const
{
	ArkString syncString = "ModelInfo {";
	syncString += "\n\tmaterialId : " + ArkString::Number(materialId);
	syncString += "\n\t,meshId : " + ArkString::Number(meshId);
	syncString += "\n\t,modelMatrix : "; // TODO (AD) Add model matrix sync
	syncString += "\n}";
	return syncString;
}



ArkString ArkRendering::MaterialInfo::Synchronize() const
{
	ArkString syncString = "MaterialInfo {";
	syncString += "\n\tresourceId\t" + ArkString::Number(id);
	syncString += "\n\tambient \t" + ambient.ToString();
	syncString += "\n\tdiffuse \t" + diffuse.ToString();
	syncString += "\n\tspecular \t" + specular.ToString();
	syncString += "\n\tshininess \t" + ArkString::Number(shininess);
	syncString += "\n\tshaderId \t" + ArkString::Number(mShaderProgram);
	syncString += "\n}";

	return syncString;
}