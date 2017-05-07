#include "ProjectManager.h"
#include "ArkDebug.h"
#include "SceneManager.h"
#include "ArkEngineCore.h"
#include "StandardLocations.h"
#include "ArkConstants.h"


ProjectManager::ProjectManager()
	: m_lock(NULL)
{
	m_lock = new ArkThreading::ArkMutex();
	subscribeToEvent(NotificationEvent::System_Startup);
}



void ProjectManager::createNewProjectWithName(ArkString name)
{
	SCOPE_LOCKER lock(m_lock, "Project Manager create new project");
	m_currentProject = new ArkProject(name); /* nothing to open so don't open project */
	m_currentProject->openProject();
}



void ProjectManager::openProject(ArkString name)
{
	SCOPE_LOCKER lock(m_lock, "Project Manager open project");

	ArkDirectory dir(name);
	if ( dir.exists() )
	{
		m_currentProject = new ArkProject(name);
		m_currentProject->openProject();
	}
	else
		Debug::Err("project " + name + " does not exist");
}



void ProjectManager::closeCurrentProject()
{
	SCOPE_LOCKER lock(m_lock, "Project Manager close project");
	m_currentProject->closeProject();
	delete m_currentProject;
	m_currentProject = NULL;
}

ArkString ProjectManager::getProjectRoot() const
{
	return StandardLocations::writeableLocation(StandardLocations::AppDataLocation) + "/ArkEngine/Projects/" + m_currentProject->getProjectName() + "/";
}



ArkString ArkProject::getProjectRoot() const
{
	return StandardLocations::writeableLocation(StandardLocations::AppDataLocation) + "/Projects/" + m_projectName + "/";
}



void ProjectManager::onNotify(NotificationEvent const * type)
{
	switch ( type->getType() )
	{
	case NotificationEvent::System_Startup:
		createNewProjectWithName("DefaultProject");
		break;
	case NotificationEvent::System_Shutdown:
		closeCurrentProject();
		break;
	default: break;
	}
}



ArkProject::ArkProject(ArkString name)
	: m_projectName(name)
{

}



void ArkProject::closeProject()
{
	eventSystem->fireEvent(NotificationEvent::System_ProjectClosed, m_projectName);
}



void ArkProject::openProject()
{
	ArkString rootPath = StandardLocations::writeableLocation(StandardLocations::AppDataLocation);
	ArkString path(rootPath + "/" + APP_NAME + "/" + "Projects/" + m_projectName);
	ArkDirectory dir(path);
	if ( !dir.exists() )
	{
		dir.mkpath();
	}
	eventSystem->fireEvent(NotificationEvent::System_ProjectOpened, m_projectName);
}