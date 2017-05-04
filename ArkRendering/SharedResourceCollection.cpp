#include "SharedResourceCollection.h"
#include "SharedResourceCollection.h"
#include "SharedResourceCollection.h"

ArkRendering::Resource * SharedResourceCollection::getResource(ResourceId id)
{
	for ( std::vector<ArkRendering::Resource *>::const_iterator it(m_resources.begin()) ; it != m_resources.end() ; it++ )
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
