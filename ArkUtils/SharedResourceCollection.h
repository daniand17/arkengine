#pragma once
#include "ArkString.h"
#include "ArkDirectory.h"
#include "Resource.h"

#include <list>

class SharedResourceCollection
{
public:
	ArkString getResourcePath() const { return m_resourcePath; }
	void setResourcePath(ArkString dirPath) { m_resourcePath = dirPath; }

	size_t size()
	{
		return m_resources.size();
	}

	Resource * getResource(ResourceId id);
	void deserializeResources();
	void serializeResources();

protected:
	ArkString m_resourcePath;

private:
	std::list<Resource *> m_resources;

};