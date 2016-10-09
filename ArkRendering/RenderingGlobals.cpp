#include "RenderingGlobals.h"
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
