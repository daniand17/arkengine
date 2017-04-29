#include "ProjectManager.h"
#include "ArkDebug.h"
#include "SceneManager.h"
#include "ArkEngineCore.h"
#include "SceneToRendererSynchronizer.h"

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
	ArkDirectory dir(name);
	bool existedBefore = dir.exists();
	if ( !existedBefore )
	{
		dir.mkdir();
	}

	for ( unsigned i = 0 ; i < ResourceType::Num_Types ; i++ )
	{
		ArkString dirPath = getProjectDirectory() + getResourceFolderName(static_cast<ResourceType>(i));
		m_resourceDirectories.push_back(dirPath);
		if ( !existedBefore )
		{
			ArkDirectory dir(m_resourceDirectories.at(i));
			dir.mkdir();
		}
	}
}



void ArkProject::openProject()
{
	setResourcesDirectories();
	deserializeProject();
}



ArkString ArkProject::getResourceDirectory(ResourceType type) const
{
	return m_resourceDirectories.at(type);
}



void ArkProject::serializeProject() const
{
	arkEngine->getResourceManager()->serializeResources();
}



void ArkProject::deserializeProject()
{
	arkEngine->getResourceManager()->deserializeResources();
	eventSystem->fireEvent(NotificationEvent::System_ProjectLoaded);
}



void ArkProject::setResourcesDirectories()
{
	ResourceManager * rm = arkEngine->getResourceManager();
	rm->setProjectDirectory(getProjectDirectory());
	rm->GetMaterialFactory()->setResourcePath(getResourceDirectory(ResourceType::Material));
	rm->GetShaderFactory()->setResourcePath(getResourceDirectory(ResourceType::Shader));
	rm->GetMeshFactory()->setResourcePath(getResourceDirectory(ResourceType::Mesh));
	rm->GetModelFactory()->setResourcePath(getResourceDirectory(ResourceType::Model));

	ArkEngineCore * engine = ArkEngineCore::Instance();
	if ( engine )
		engine->getSceneManager()->setSceneDirectory(getResourceDirectory(ResourceType::Scene));
}



ArkString ArkProject::getResourceFolderName(ResourceType type) const
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
