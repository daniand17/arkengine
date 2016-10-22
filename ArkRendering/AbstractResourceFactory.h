#pragma once

#include "ArkString.h"
class ResourceFactory
{
public:
	virtual void DesynchronizeResources(ArkString projectName) = 0;
	virtual void SynchronizeResources(ArkString projectName) = 0;
};