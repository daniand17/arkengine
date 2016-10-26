#pragma once

#include "ArkString.h"
class ResourceFactory
{
public:
	void setPathToResourceDirectory(ArkString path) { m_pathToResourceDirectory = path; }
	virtual void DesynchronizeResources(ArkString projectName) = 0;
	virtual void SynchronizeResources(ArkString projectName) = 0;
	virtual size_t size() const = 0;
	virtual void clear() = 0;

	ArkString m_pathToResourceDirectory;
};