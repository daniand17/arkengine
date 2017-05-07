#pragma once

#include "ArkString.h"


typedef unsigned int ResourceId;

struct Resource
{
	ArkString m_name;
	ResourceId m_id;

	ArkString getName() const { return m_name; }
	ResourceId getId() const { return m_id; }

	virtual void serialize(ArkString absFilepath) const = 0;
	virtual void deserialize(ArkString absFilepath) const = 0;
};