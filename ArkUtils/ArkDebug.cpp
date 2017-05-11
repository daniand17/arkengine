	#include "ArkDebug.h"

void Debug::Log(ArkString string)
{
	std::cout << string << std::endl;
}

void Debug::Err(ArkString string)
{
	std::cerr << string << std::endl;
}