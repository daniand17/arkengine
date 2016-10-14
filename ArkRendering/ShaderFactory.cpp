#include "ShaderFactory.h"

using namespace ArkRendering;

Resource_Id ShaderFactory::CreateShader(ArkString vertexShaderName, ArkString fragmentShaderName)
{
	AllocatedShader newShader;
	newShader.id = mShaders.size();
	newShader.vertexShaderName = vertexShaderName;
	newShader.fragmentShaderName = fragmentShaderName;
	newShader.shader = new ShaderProgram(vertexShaderName, fragmentShaderName);
	mShaders.push_back(newShader);
	return newShader.id;
}

ArkRendering::ShaderProgram * ShaderFactory::GetShaderProgramByResourceId(Resource_Id programId) const
{
	return programId >= 0 && programId < mShaders.size() ? 
		mShaders[programId].shader : 
		NULL;
}