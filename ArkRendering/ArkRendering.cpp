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
	, m_shaderName("")
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


ArkRendering::ShaderProgram::ShaderProgram(ArkString name, ArkString vertexShader, ArkString fragmentShader)
	: m_vertexShader(vertexShader)
	, m_fragmentShader(fragmentShader)
	, m_numAttributes(0)
	, m_numUniforms(0)
	, m_programId(0)
	, m_texture(NULL)
{
	m_name = name;
}


ArkString ArkRendering::ShaderProgram::serialize() const
{
	ArkString sync("ShaderProgram");
	sync += "\n\tname:" + m_name;
	sync += "\n\tvertexShader:" + getVertexShaderName();
	sync += "\n\tfragmentShader:" + getFragmentShaderName();
	return sync;
}


void ArkRendering::ShaderProgram::compileAndLoadShader()
{
	m_programId = LoadShaders(m_vertexShader.c_str(), m_fragmentShader.c_str());
	glGetProgramInterfaceiv(m_programId, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &m_numAttributes);
	glGetProgramInterfaceiv(m_programId, GL_UNIFORM, GL_ACTIVE_RESOURCES, &m_numUniforms);
	// TODO (AD) code to get more info about a shaders attrs http://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shade
}


void ArkRendering::ShaderProgram::unloadShader()
{
	glDeleteProgram(m_programId);
	delete m_texture;
}


ArkString ArkRendering::MeshInfo::serialize() const
{
	ArkString syncString = "MeshInfo";
	syncString += "\n\tname:" + name;
	return syncString;
}


ArkString ArkRendering::ModelInfo::serialize() const
{
	ArkString syncString = "ModelInfo";
	syncString += "\n\tname:" + m_name;
	syncString += "\n\tmesh:" + m_mesh;
	syncString += "\n\tmaterial:" + m_material;
	return syncString;
}


ArkString ArkRendering::MaterialInfo::serialize() const
{
	ArkString syncString = "MaterialInfo";
	syncString += "\n\tname:" + m_name;
	syncString += "\n\tambient:" + ambient.ToString();
	syncString += "\n\tdiffuse:" + diffuse.ToString();
	syncString += "\n\tspecular:" + specular.ToString();
	syncString += "\n\tshininess:" + ArkString::Number(shininess);
	syncString += "\n\tshader:" + m_shaderName;

	return syncString;
}