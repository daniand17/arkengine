#include "ProjectManager.h"
#include "ArkDebug.h"
#include "SceneManager.h"
#include "ArkEngineCore.h"
ProjectManager * ProjectManager::sm_instance = NULL;

void ProjectManager::Initialize()
{
	if ( !sm_instance )
	{
		Debug::Log("Initializing ProjectManager");
		sm_instance = new ProjectManager();
	}
}


ProjectManager::ProjectManager()
	: m_lock(NULL)
{
	m_lock = new ArkThreading::ArkMutex();
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


ArkProject::ArkProject(ArkString name)
	: m_projectName(name)
	, m_projectDirectory(name)
{
	bool existedBefore = m_projectDirectory.exists();

	if ( !existedBefore )
	{
		m_projectDirectory.createDirectory();

	}

	for ( unsigned i = 0 ; i < ResourceType::Num_Types ; i++ )
	{
		ArkString dirPath = getProjectDirectory() + getResourceFolderName(static_cast<ResourceType>(i));
		m_resourceDirectories.push_back(new ArkDirectory(dirPath));
		if ( !existedBefore )
			m_resourceDirectories.at(i)->createDirectory();
	}
}


void ArkProject::openProject()
{
	setResourcesDirectories();
	deserializeProject();
}


ArkDirectory * ArkProject::getResourceDirectory(ResourceType type) const
{
	return m_resourceDirectories.at(type);
}


void ArkProject::serializeProject() const
{
	// TODO (AD) synchronize project settings
	ResourceManager::Instance()->serializeResources();
}


void ArkProject::deserializeProject()
{
	// TODO (AD) desynchronize project settings
	if ( ResourceManager::Instance() )
	{
		ResourceManager::Instance()->deserializeResources();
	}
}

void ArkProject::setResourcesDirectories()
{
	ResourceManager * rm = ResourceManager::Instance();
	if ( !rm ) return;
	rm->setProjectDirectory(getProjectDirectory());
	rm->GetMaterialFactory()->setDirectory(getResourceDirectory(ResourceType::Material));
	rm->GetShaderFactory()->setDirectory(getResourceDirectory(ResourceType::Shader));
	rm->GetMeshFactory()->setDirectory(getResourceDirectory(ResourceType::Mesh));
	rm->GetModelFactory()->setDirectory(getResourceDirectory(ResourceType::Model));

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
