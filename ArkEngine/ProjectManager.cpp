#include "ProjectManager.h"
#include "ArkDebug.h"
#include "SystemDirectory.h"

ProjectManager * ProjectManager::sm_instance = NULL;
ArkThreading::ArkMutex ProjectManager::sm_lock;


void ProjectManager::Initialize()
{
	if ( !sm_instance )
	{
		sm_lock.lock();
		Debug::Log("Initializing ProjectManager");
		sm_instance = new ProjectManager();
		sm_lock.unlock();
	}
}


void ProjectManager::createNewProjectWithName(ArkString name)
{
	sm_lock.lock();

	m_currentProject = new ArkProject(name); /* nothing to open so don't open project */

	SystemDirectory::createDirectory(name);
	SystemDirectory::createDirectory(name + "/resources");
	m_currentProject->openProject();
	sm_lock.unlock();
}


void ProjectManager::openProject(ArkString name)
{
	sm_lock.lock();
	if ( SystemDirectory::directoryExists(name) )
	{
		m_currentProject = new ArkProject(name);
		m_currentProject->openProject();
	}
	else
		Debug::Err("project " + name + " does not exist");

	sm_lock.unlock();
}

void ProjectManager::closeCurrentProject()
{
	m_currentProject->closeProject();
	delete m_currentProject;
	m_currentProject = NULL;
}


ArkProject::ArkProject(ArkString name)
	:m_projectName(name)
{
}


void ArkProject::synchronizeProject() const
{
	// TODO (AD) synchronize project settings
	ResourceManager::Instance()->synchronizeResources(getResourcesDirectory());
}


void ArkProject::desynchronizeProject()
{
	// TODO (AD) desynchronize project settings
	if ( ResourceManager::Instance() )
		ResourceManager::Instance()->desynchronizeResources(getResourcesDirectory());
}
