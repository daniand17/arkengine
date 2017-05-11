#pragma once

#include "ArkString.h"
#include "YAML_Util.h"

struct ProjectResource
{
public:
	// NOTE: This is also the order in which resources are deserialized
	enum ResourceTypes
	{
		RT_Unsupported = -1,
		RT_Shader,
		RT_Texture,
		RT_Material,
		RT_Mesh,
		RT_Scene,

		RT_NumTypes
	};

	ProjectResource(ArkString name, ArkString filename, ResourceTypes type);

	ArkString getName() const { return m_name; }

	virtual void serialize() const = 0;
	virtual void deserialize() = 0;

	ResourceTypes getType() const { return m_type; }

	static ResourceTypes getResourceTypeFromExtension(ArkString name);


protected:
	ArkString m_filename;
	ArkString m_name;
	ResourceTypes m_type;
};