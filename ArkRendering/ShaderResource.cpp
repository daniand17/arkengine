#include "ShaderResource.h"
#include "ArkFile.h"

ShaderResource::ShaderResource(ArkString name, ArkString filepath)
	: ProjectResource(name, filepath, RT_Shader)
	, m_shaderSource("")
{

}



void ShaderResource::deserialize()
{
	// TODO (AD) implement deserialize for shader resource
	ArkFile file(m_filename);

	if ( file.exists() )
	{
		m_shaderSource = file.readAll();
	}
}



void ShaderResource::serialize() const
{
	// TODO (AD) implement serialize for shader resource
}
