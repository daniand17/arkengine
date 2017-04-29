#pragma once
#include "ArkString.h"
#include "Filesystem.h"
#include "ArkRendering.h"

class ResourceFactory
{
public:
	ArkString getResourcePath() const { return m_resourcePath; }
	void setResourcePath(ArkString dirPath) { m_resourcePath = dirPath; }
	
	virtual size_t size() const = 0;
	virtual ArkRendering::Resource * getResourceByName(ArkString name) = 0;
	
	virtual void deserializeResources() = 0;
	virtual void serializeResources() = 0;
	virtual void clear() = 0;

protected:
	ArkString m_resourcePath;
};