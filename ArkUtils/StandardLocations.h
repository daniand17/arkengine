#pragma once

#include "ArkString.h"

class StandardLocations
{
public:
	enum Location
	{
		AppDataLocation
	};

	static ArkString writeableLocation(Location location);
};