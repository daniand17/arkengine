#pragma once
#include "ArkThread.h"
#include "ResourceManager.h"
#include "ArkString.h"
#include "ArkDirectory.h"
#include "SystemNotifications.h"

class ArkProject
{
public:
	ArkProject(ArkString name);
	void setProjectName(ArkString projectName) { m_projectName = projectName; }

	void closeProject();
	void openProject();

	ArkString getProjectName() const { return m_projectName; }
	ArkString getProjectDirectory() const { return m_projectName + "/"; }

private:
	ArkString m_projectName;
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

	ArkString getProjectRoot() const;

private:
	ArkThreading::ArkMutex * m_lock;
	ArkProject * m_currentProject;

	// Inherited via NotificationSubscriber
	virtual void onNotify(NotificationEvent const * type) override;
};