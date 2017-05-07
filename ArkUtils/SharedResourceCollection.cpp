#include "SharedResourceCollection.h"

Resource * SharedResourceCollection::getResource(ResourceId id)
{
	for ( std::vector<Resource *>::const_iterator it(m_resources.begin()) ; it != m_resources.end() ; it++ )
	{
		if ( (*it)->m_id == id )
		{
			return (*it);
		}
	}
	return NULL;
}

void SharedResourceCollection::deserializeResources()
{
}

void SharedResourceCollection::serializeResources()
{
}
