#pragma once

#include "ArkThread.h"
#include "SystemNotifications.h"
#include "SharedResourceCollection.h"

class ResourceManager : NotificationSubscriber
{
public:
	enum ResourceType
	{
		Mesh,
		Material,
		Model,
		Shader,
		Meta,
		Scene,
		Num_Types

	};

	ResourceManager();
	~ResourceManager();

	void setProjectDirectory(ArkString directory) { m_projectDirectory = directory; }

	void serializeResources();
	void deserializeResources();

	ArkThreading::ArkMutex * getLock() const { return m_lock; }

protected:
	// Inherited via NotificationSubscriber
	virtual void onNotify(NotificationEvent const * notificationEvent) override;


private:
	ArkThreading::ArkMutex * m_lock;
	ArkString m_projectDirectory;

	SharedResourceCollection * m_materialCollection;
	SharedResourceCollection * m_meshCollection;
	SharedResourceCollection * m_modelCollection;
	SharedResourceCollection * m_shaderCollection;

	ArkString getResourceFolderName(ResourceType type) const;
	ArkString getResourceDirectory(ResourceType resourceType) const;
};