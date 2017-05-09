#include "SharedResourceCollection.h"

Resource * SharedResourceCollection::getResource(ResourceId id)
{
	for ( std::list<Resource *>::const_iterator it(m_resources.begin()) ; it != m_resources.end() ; it++ )
	{
		if ( (*it)->getId() == id )
		{
			return (*it);
		}

	}
	return NULL;
}



void SharedResourceCollection::deserializeResources()
{
	ArkDirectory dir(m_resourcePath);

	if ( dir.exists() )
	{
		ArkStringList filelist = dir.getFileList();

	}
}



void SharedResourceCollection::serializeResources()
{
	for ( std::list<Resource *>::const_iterator it(m_resources.begin()) ; it != m_resources.end() ; it++ )
	{
		Resource * resource(*it);

		resource->serialize(m_resourcePath + resource->getName() + "." + resource->getResourceFileExtension());

	}
}
