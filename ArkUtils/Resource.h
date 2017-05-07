#pragma once

#include "ArkString.h"


typedef unsigned int ResourceId;

struct Resource
{
	ArkString m_name;
	ResourceId m_id;
	virtual ArkString serialize() const = 0;
	virtual void deserialize() const = 0;
};