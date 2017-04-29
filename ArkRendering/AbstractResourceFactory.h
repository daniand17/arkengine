#pragma once
#include "ArkString.h"
#include "Filesystem.h"
#include "ArkRendering.h"

class ResourceFactory
{
public:
	ArkDirectory * getDirectory() const { return m_directory; }
	void setDirectory(ArkDirectory * directory) { m_directory = directory; }
	
	virtual unsigned int size() const = 0;
	virtual ArkRendering::Resource * getResourceByName(ArkString name) = 0;
	
	virtual void deserializeResources() = 0;
	virtual void serializeResources() = 0;
	virtual void clear() = 0;

protected:
	ArkDirectory * m_directory;
};