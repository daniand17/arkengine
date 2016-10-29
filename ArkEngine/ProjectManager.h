#pragma once
#include "ArkThread.h"
#include "ResourceManager.h"
#include "ArkString.h"
#include "Filesystem.h"

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
		Num_Types

	};

	ArkProject(ArkString name);
	void setProjectName(ArkString projectName) { m_projectName = projectName; }

	void closeProject() { serializeProject(); }
	void openProject();

	ArkString getProjectName() const { return m_projectName; }
	ArkString getProjectDirectory() const { return m_projectName + "/"; }
	ArkDirectory * getResourceDirectory(ResourceType type) const;


private:
	ArkString m_projectName;
	void serializeProject() const;
	void deserializeProject();

	void setResourcesDirectories(); 

	ArkDirectory m_projectDirectory;
	ArkString getResourceFolderName(ResourceType type) const;

	std::vector<ArkDirectory *> m_resourceDirectories;
};

class ProjectManager
{
public:
	static void Initialize();
	static ProjectManager * ProjectManager::Instance() { return sm_instance; }

	ProjectManager();
	void createNewProjectWithName(ArkString name);
	void openProject(ArkString name);
	void closeCurrentProject();
	ArkProject * getCurrentProject() const { return m_currentProject; }

private:
	static ProjectManager * sm_instance;
	ArkThreading::ArkMutex * m_lock;
	ArkProject * m_currentProject;
};