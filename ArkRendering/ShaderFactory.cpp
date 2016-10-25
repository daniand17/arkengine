#include "ShaderFactory.h"
#include "Filestream.h"

using namespace ArkRendering;

Resource_Id ShaderFactory::CreateShader(ArkString vertexShaderName, ArkString fragmentShaderName)
{
	ShaderProgram * shader = new ShaderProgram(vertexShaderName, fragmentShaderName);
	shader->id = m_loadedShaders.size();
	shader->setVertexShader(vertexShaderName);
	shader->setFragmentShader(fragmentShaderName);
	m_loadedShaders.push_back(shader);
	return shader->id;
}


ArkRendering::ShaderProgram * ShaderFactory::GetShaderProgramByResourceId(Resource_Id programId) const
{
	return programId >= 0 && programId < m_loadedShaders.size()
		? m_loadedShaders[programId]
		: NULL;
}


void ShaderFactory::DesynchronizeResources(ArkString projectName)
{
	Filestream inFile(projectName, "shaders");
	inFile.OpenFile(Filestream::FileOpenType::Read);
	ArkString fileContents("");
	inFile.ReadAll(&fileContents);

	if ( fileContents.length() > 0 )
	{
		ArkStringList list = fileContents.split(',');

		for ( unsigned i = 0 ; i < list.size() ; i++ )
		{
			createShaderFromString(list.at(i));
		}
	}
}


void ShaderFactory::SynchronizeResources(ArkString projectName)
{
	Filestream outfile(projectName, "shaders");
	try { outfile.OpenFile(Filestream::FileOpenType::Write); }
	catch ( std::exception & e ) { e.what(); }

	ArkString syncString("");
	for ( size_t i = 0 ; i < m_loadedShaders.size() ; i++ )
	{
		syncString += m_loadedShaders[i]->Synchronize();

		if ( i < m_loadedShaders.size() - 1 )
			syncString += "\n,";
	}

	outfile.WriteStringToFile(syncString);
	outfile.CloseFile();
}


void ShaderFactory::clear()
{
	while ( m_loadedShaders.size() > 0 )
	{
		delete m_loadedShaders.at(m_loadedShaders.size() - 1);
		m_loadedShaders.pop_back();
	}
}


void ShaderFactory::createShaderFromString(ArkString theString)
{
	if ( theString.length() > 0 )
	{
		ArkStringList list = theString.split('\n');

		_ASSERT_EXPR(list.size() == 4, "ShaderFactory.cpp(80)");
		CreateShader(list.at(2).split(':').at(1), list.at(3).split(':').at(1));
	}
}



void ShaderFactory::compileShaders()
{
	for ( size_t i = 0 ; i < m_loadedShaders.size() ; i++ )
		m_loadedShaders[i]->compileAndLoadShader();
}