#include "ShaderFactory.h"

ShaderProgram const * ShaderFactory::createShaderProgram(ShaderResource const * vertexShader, ShaderResource const * fragmentShader)
{
	ArkString shaderName(genNameFromShaders(vertexShader, fragmentShader));
	ShaderProgram * prog;
	if ( m_programs.find(shaderName) == m_programs.end() )
	{
		prog = new ShaderProgram();
		prog->compileAndLoadShader(vertexShader->getSource(), fragmentShader->getSource());
		m_programs.insert(std::pair<ArkString, ShaderProgram *>(shaderName, prog));
	}
	else
	{
		prog = m_programs.at(shaderName);
	}

	return prog;
}



bool ShaderFactory::hasShaderProgramForShaders(ShaderResource const * vert, ShaderResource const * frag) const
{
	return m_programs.find(genNameFromShaders(vert, frag)) != m_programs.end();
}



ShaderProgram const * ShaderFactory::getProgramForShaders(ShaderResource const * vertexShader, ShaderResource const * fragmentShader)
{
	if ( hasShaderProgramForShaders(vertexShader, fragmentShader) )
	{
		return m_programs.at(genNameFromShaders(vertexShader, fragmentShader));
	}

	return NULL;
}



void ShaderFactory::addShaderToFactory(ShaderResource const * shader)
{
	m_shaders.push_back(shader);
}



ShaderResource const * ShaderFactory::getShaderByName(ArkString name) const
{
	for(std::list<ShaderResource const *>::const_iterator it(m_shaders.begin()); it != m_shaders.end(); it++)
	{
		if ( (*it)->getName() == name )
		{
			return *it;
		}
	}

	return NULL;
}



ArkString ShaderFactory::genNameFromShaders(ShaderResource const * vert, ShaderResource const * frag) const
{
	return vert->getName() + frag->getName();
}