#pragma once

#include "ShaderProgram.h"
#include "ArkString.h"
#include "ShaderResource.h"
#include <map>
#include "SystemNotifications.h"


class ShaderFactory
{
public:

	ShaderProgram const * createShaderProgram(ShaderResource const * vertexShader, ShaderResource const * fragmentShader);

	bool hasShaderProgramForShaders(ShaderResource const * vert, ShaderResource const * frag) const;
	ShaderProgram const * getProgramForShaders(ShaderResource const * vertexShader, ShaderResource const * fragmentShader);

	void addShaderToFactory(ShaderResource const * shader);
	ShaderResource const * getShaderByName(ArkString name) const;

	void clearAllShaders() { m_shaders.clear(); }

	// TODO (AD) Make sure to delete programs when project closes

private:
	std::map<ArkString, ShaderProgram *> m_programs;
	ArkString genNameFromShaders(ShaderResource const * vert, ShaderResource const * frag) const;

	std::list<ShaderResource const *> m_shaders;
};