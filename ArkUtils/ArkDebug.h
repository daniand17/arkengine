#pragma once
#include <iostream>

#include "ArkString.h"

namespace Debug
{
	void Log(ArkString string)
	{
		std::cout << string << std::endl;
	}

	void Err(ArkString string)
	{
		std::cerr << string << std::endl;
	}
}