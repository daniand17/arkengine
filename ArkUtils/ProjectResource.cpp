#include "ProjectResource.h"

ProjectResource::ProjectResource(ArkString name, ArkString filename, ResourceTypes type)
	: m_filename(filename)
	, m_name(name)
	, m_type(type)
{
}



ProjectResource::ResourceTypes ProjectResource::getResourceTypeFromExtension(ArkString name)
{

	if ( name == "bmp" )
	{
		return RT_Texture;
	}

	else if ( name == "scene" )
	{
		return RT_Scene;
	}

	else if ( name == "vert" || name == "frag" )
	{
		return RT_Shader;
	}

	else if ( name == "obj" )
	{
		return RT_Mesh;
	}

	else if ( name == "material" )
	{
		return RT_Material;
	}

	return RT_Unsupported;
}