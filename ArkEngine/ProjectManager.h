#pragma once
#include "ArkThread.h"
#include "ResourceManager.h"
#include "ArkString.h"

class ArkProject
{
public:
	ArkProject(ArkString name);
	ArkString getProjectName() const { return m_projectName; }
	void setProjectName(ArkString projectName) { m_projectName = projectName; }

	void closeProject() { synchronizeProject(); }
	void openProject() { desynchronizeProject(); }

	ArkString getResourcesDirectory() const { return m_projectName + "/resources/"; }
	ArkString getProjectDirectory() const { return m_projectName + "/"; }

private:
	ArkString m_projectName;
	void synchronizeProject() const;
	void desynchronizeProject();
};

class ProjectManager
{
public:
	static void Initialize();
	static ProjectManager * ProjectManager::Instance() { return sm_instance; }
	void createNewProjectWithName(ArkString name);
	void openProject(ArkString name);
	void closeCurrentProject() { m_currentProject->closeProject(); }
	ArkProject * getCurrentProject() const { return m_currentProject; }

private:
	static ProjectManager * sm_instance;
	static ArkThreading::ArkMutex sm_lock;
	ArkProject * m_currentProject;
};