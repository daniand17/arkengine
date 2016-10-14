#pragma once
#include <vector>

#include "ArkRendering.h"

class ShaderFactory
{
public:
	Resource_Id CreateShader(ArkString vertexShader, ArkString fragmentShader);
	ArkRendering::ShaderProgram * GetShaderProgramByResourceId(Resource_Id programId) const;

private:
	struct AllocatedShader
	{
		Resource_Id id;
		ArkString vertexShaderName;
		ArkString fragmentShaderName;
		ArkRendering::ShaderProgram * shader;
	};

	std::vector<AllocatedShader> mShaders;
};