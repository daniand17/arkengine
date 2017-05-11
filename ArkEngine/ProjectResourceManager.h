#pragma once

#include "ArkThread.h"
#include "SystemNotifications.h"
#include "ProjectResource.h"
#include <map>


class ProjectResourceManager : NotificationSubscriber
{
public:
	ProjectResourceManager();
	~ProjectResourceManager();

	void setProjectDirectory(ArkString directory) { m_projectDirectory = directory; }

	void serializeResources();
	void deserializeResources();

	ProjectResource * getResourceByName(ArkString name) const;
	std::list<ProjectResource *> getResourcesByType(ProjectResource::ResourceTypes type) const;

	ArkThreading::ArkMutex * getLock() const { return m_lock; }

protected:
	// Inherited via NotificationSubscriber
	virtual void onNotify(NotificationEvent const * notificationEvent) override;
	void genAndDeserializeProjectResources();
	void genFilelist(ArkStringList &allFiles);


private:
	ArkThreading::ArkMutex * m_lock;
	ArkString m_projectDirectory;

	std::map<ArkString, ProjectResource *> m_resourceMap;
	std::map<ProjectResource::ResourceTypes, std::list<ProjectResource *>> m_resourceTypeMap;

};