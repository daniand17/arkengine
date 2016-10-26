#pragma once
#include "ArkThread.h"
#include "ResourceManager.h"
#include "ArkString.h"

class ArkProject
{
public:
	enum ResourceType
	{
		Mesh,
		Material,
		Model,
		Shader,
		Num_Types

	};

	ArkProject(ArkString name);
	ArkString getProjectName() const { return m_projectName; }
	void setProjectName(ArkString projectName) { m_projectName = projectName; }

	void closeProject() { serializeProject(); }
	void openProject();

	ArkString getMetaDirectory() const { return m_projectName + "/meta/"; }
	ArkString getProjectDirectory() const { return m_projectName + "/"; }
	ArkString getResourceDirectory(ResourceType type);


private:
	ArkString m_projectName;
	void serializeProject() const;
	void deserializeProject();

	void setResourcesDirectories(); 
};

class ProjectManager
{
public:
	static void Initialize();
	static ProjectManager * ProjectManager::Instance() { return sm_instance; }
	void createNewProjectWithName(ArkString name);
	void openProject(ArkString name);
	void closeCurrentProject();
	ArkProject * getCurrentProject() const { return m_currentProject; }

private:
	static ProjectManager * sm_instance;
	static ArkThreading::ArkMutex sm_lock;
	ArkProject * m_currentProject;
};