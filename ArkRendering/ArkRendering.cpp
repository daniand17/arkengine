#include "ArkRendering.h"
#include "ShaderLoader.h"
#include "ImageLoader.h"
#include "ArkAssert.h"
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


ArkRendering::MaterialInfo::MaterialInfo()
	: ambient(Vec3::one())
	, diffuse(Vec3::one())
	, specular(Vec3::one())
	, shininess(0.0f)
	, m_shaderProgram(NULL)
	, m_shaderProgramId(0)
	, shiId(0)
	, ambId(0)
	, difId(0)
	, spcId(0)
	, m_bound(false)
{
}


void ArkRendering::MaterialInfo::setShaderProgram(ArkRendering::ShaderProgram * shaderProgram)
{
	m_shaderProgram = shaderProgram;
	getVertexBindingsFromShader();
}

void ArkRendering::MaterialInfo::useShaderProgram() const
{

	glUseProgram(m_shaderProgram->getId());
	pushValuesToRenderer();
}


void ArkRendering::MaterialInfo::pushValuesToRenderer() const
{
	glUniform3f(ambId, ambient.x, ambient.y, ambient.z);
	glUniform3f(difId, diffuse.x, diffuse.y, diffuse.z);
	glUniform3f(spcId, specular.x, specular.y, specular.z);
	glUniform1f(shiId, shininess);

}

void ArkRendering::MaterialInfo::getVertexBindingsFromShader()
{
	if ( !m_bound && m_shaderProgram != NULL )
	{
		m_bound = true;
		GLuint shaderProgramId = m_shaderProgram->getId();
		glUseProgram(shaderProgramId);
		ambId = glGetUniformLocation(shaderProgramId, "material.ambient");
		difId = glGetUniformLocation(shaderProgramId, "material.diffuse");
		spcId = glGetUniformLocation(shaderProgramId, "material.specular");
		shiId = glGetUniformLocation(shaderProgramId, "material.shininess");
	}
}


ArkRendering::ShaderProgram::ShaderProgram(ArkString vertexShader, ArkString fragmentShader)
	: m_vertexShader(vertexShader)
	, m_fragmentShader(fragmentShader)
{
}


ArkString ArkRendering::ShaderProgram::Synchronize() const
{
	ArkString sync("ShaderProgram");
	sync += "\n\tid:" + ArkString::Number(id);
	sync += "\n\tvertexShader:" + m_vertexShader;
	sync += "\n\tfragmentShader:" + m_fragmentShader;
	return sync;
}


void ArkRendering::ShaderProgram::compileAndLoadShader()
{
	mProgramId = LoadShaders(m_vertexShader.c_str(), m_fragmentShader.c_str());
	glGetProgramInterfaceiv(mProgramId, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &mNumAttributes);
	glGetProgramInterfaceiv(mProgramId, GL_UNIFORM, GL_ACTIVE_RESOURCES, &mNumUniforms);
	// TODO (AD) code to get more info about a shaders attrs http://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shade
}



void ArkRendering::ShaderProgram::unloadShader()
{
	glDeleteProgram(mProgramId);
	delete mTexture;
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
	syncString += "\n\tshaderId \t" + ArkString::Number(m_shaderProgramId);
	syncString += "\n}";

	return syncString;
}