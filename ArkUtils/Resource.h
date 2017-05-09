#pragma once

#include "ArkString.h"


typedef unsigned int ResourceId;

struct Resource
{
public:
	ArkString getName() const { return m_name; }
	void setName(ArkString set) { m_name = set; }
	ResourceId getId() const { return m_id; }
	void setId(ResourceId id) { m_id = id; }

	virtual void serialize(ArkString absFilepath) const = 0;
	virtual void deserialize(ArkString absFilepath) const = 0;

	virtual ArkString getResourceFileExtension() const = 0;

protected:

	ArkString m_name;
	ResourceId m_id;
};