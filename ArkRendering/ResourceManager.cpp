#include "ResourceManager.h"
#include "ArkDebug.h"
#include "ArkAssert.h"
#include "StandardLocations.h"

using namespace ArkThreading;

ResourceManager::ResourceManager()
	: m_lock(NULL)
	, m_materialCollection(NULL)
	, m_shaderCollection(NULL)
	, m_meshCollection(NULL)
	, m_modelCollection(NULL)
{
	subscribeToEvent(NotificationEvent::System_ProjectOpened);
	subscribeToEvent(NotificationEvent::System_ProjectClosed);

	m_materialCollection = new SharedResourceCollection();
	m_shaderCollection = new SharedResourceCollection();
	m_meshCollection = new SharedResourceCollection();
	m_modelCollection = new SharedResourceCollection();
}



ResourceManager::~ResourceManager()
{
	delete m_lock;
	delete m_materialCollection;
	delete m_shaderCollection;
	delete m_meshCollection;
	delete m_modelCollection;
}



void ResourceManager::deserializeResources()
{
	SCOPE_LOCKER lock(getLock(), "Deserialize ResourceManager");
	m_materialCollection->deserializeResources();
	m_shaderCollection->deserializeResources();
	m_meshCollection->deserializeResources();
	m_modelCollection->deserializeResources();
}



void ResourceManager::onNotify(NotificationEvent const * notificationEvent)
{
	switch ( notificationEvent->getType() )
	{
	case NotificationEvent::EventType::System_ProjectOpened:
		m_materialCollection->setResourcePath(getResourceDirectory(ResourceType::Material));
		m_shaderCollection->setResourcePath(getResourceDirectory(ResourceType::Shader));
		m_meshCollection->setResourcePath(getResourceDirectory(ResourceType::Mesh));
		m_modelCollection->setResourcePath(getResourceDirectory(ResourceType::Model));
		break;
	}
}



void ResourceManager::serializeResources()
{
	SCOPE_LOCKER lock(getLock(), "Serialize ResourceManager");
	m_materialCollection->serializeResources();
	m_shaderCollection->serializeResources();
	m_meshCollection->serializeResources();
	m_modelCollection->serializeResources();
}



ArkString ResourceManager::getResourceFolderName(ResourceType type) const
{
	switch ( type )
	{
	case Mesh:		return "meshes/";
	case Material:	return "materials/";
	case Model:		return "models/";
	case Shader:	return "shaders/";
	case Meta:		return "meta/";
	case Scene:		return "scenes/";
	default:		return "meta/";
	}
}



ArkString ResourceManager::getResourceDirectory(ResourceType resourceType) const
{
	return StandardLocations::writeableLocation(StandardLocations::AppDataLocation) + "/Projects/" + getResourceFolderName(resourceType);
}
