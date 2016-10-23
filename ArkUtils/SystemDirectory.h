#pragma once
#include "ArkString.h"
#include "ArkDebug.h"

class SystemDirectory
{
public:
	static bool createDirectory(ArkString directoryName);
	static bool directoryExists(ArkString directory);
	
};