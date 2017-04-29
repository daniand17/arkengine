#pragma once
#include "ArkThread.h"
#include "ResourceManager.h"
#include "ArkString.h"
#include "Filesystem.h"
#include "SystemNotifications.h"

class ArkProject
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

	ArkProject(ArkString name);
	void setProjectName(ArkString projectName) { m_projectName = projectName; }

	void closeProject() { serializeProject(); }
	void openProject();

	ArkString getProjectName() const { return m_projectName; }
	ArkString getProjectDirectory() const { return m_projectName + "/"; }
	ArkString getResourceDirectory(ResourceType type) const;


private:
	ArkString m_projectName;
	void serializeProject() const;
	void deserializeProject();

	void setResourcesDirectories(); 

	ArkString getResourceFolderName(ResourceType type) const;

	std::vector<ArkString> m_resourceDirectories;
};

class ProjectManager : public NotificationSubscriber
{
public:
	ProjectManager();
	void createNewProjectWithName(ArkString name);
	void openProject(ArkString name);
	void closeCurrentProject();
	ArkProject * getCurrentProject() const { return m_currentProject; }

private:
	ArkThreading::ArkMutex * m_lock;
	ArkProject * m_currentProject;

	// Inherited via NotificationSubscriber
	virtual void onNotify(NotificationEvent const * type) override;
};