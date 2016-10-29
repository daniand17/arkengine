#include "ShaderFactory.h"
#include "Filestream.h"
#include "ArkAssert.h"

using namespace ArkRendering;

void ShaderFactory::CreateShader(ArkString shaderName, ArkString vertexShaderName, ArkString fragmentShaderName)
{
	ShaderProgram * shader = new ShaderProgram(shaderName, vertexShaderName, fragmentShaderName);
	shader->setVertexShader(vertexShaderName);
	shader->setFragmentShader(fragmentShaderName);
	m_loadedShaders.insert(ShaderNamePair(shader->m_name, shader));
}


void ShaderFactory::deserializeResources()
{
	ArkString fileContents;
	if ( m_directory->fileExists("shaders.meta") )
	{
		ArkFile * file = m_directory->getFileByFilename("shaders.meta");
		fileContents = file->getFileContents();
	}

	if ( fileContents.length() > 0 )
	{
		ArkStringList list = fileContents.split(',');
		for ( unsigned i = 0 ; i < list.size() ; i++ )
			createShaderFromString(list.at(i));
	}
}


void ShaderFactory::serializeResources()
{	
	ArkString syncString("");
	for ( auto iter = m_loadedShaders.begin() ; iter != m_loadedShaders.end() ; iter++ )
	{
		if ( iter != m_loadedShaders.begin() )
			syncString += "\n,";
		syncString += iter->second->serialize();
	}

	ArkFile * file = 
		m_directory->fileExists("shaders.meta") 
		? m_directory->getFileByFilename("shaders.meta") 
		: m_directory->createFile("shaders", "meta");

	file->writeToFile(syncString);
}


void ShaderFactory::clear()
{
	for ( auto iter = m_loadedShaders.begin() ; iter != m_loadedShaders.end() ; iter++ )
		delete iter->second;

	m_loadedShaders.clear();
}

ArkRendering::ShaderProgram * ShaderFactory::getResourceByName(ArkString name)
{
	auto iter = m_loadedShaders.find(name);
	return iter != m_loadedShaders.end() ? iter->second : NULL;
}


void ShaderFactory::createShaderFromString(ArkString theString)
{
	if ( theString.length() > 0 )
	{
		ArkStringList list = theString.split('\n');

		// Need to get the project here
		ARK_ASSERT(list.size() >= 4, "Expected at least 3 lines in a shader");
		ArkString shaderName = list.at(1).split(':').at(1);
		ArkString vertShaderName = m_directory->getAbsolutePath() + list.at(2).split(':').at(1);
		ArkString fragShaderName = m_directory->getAbsolutePath() + list.at(3).split(':').at(1);

		CreateShader(shaderName, vertShaderName, fragShaderName);
	}
}


void ShaderFactory::compileShaders()
{
	for ( auto iter = m_loadedShaders.begin() ; iter != m_loadedShaders.end() ; iter++ )
		iter->second->compileAndLoadShader();
}