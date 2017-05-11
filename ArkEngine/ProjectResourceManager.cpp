#include "ProjectResourceManager.h"
#include "ArkDebug.h"
#include "ArkAssert.h"
#include "StandardLocations.h"
#include "ArkEngineCore.h"
#include "ProjectManager.h"
#include "ShaderResource.h"
#include "MeshResource.h"

using namespace ArkThreading;

ProjectResourceManager::ProjectResourceManager()
	: m_lock(NULL)
{
	subscribeToEvent(NotificationEvent::Project_Opened);
	subscribeToEvent(NotificationEvent::Project_Closed);

	m_lock = new ArkMutex();

	for ( size_t i = 0 ; i < ProjectResource::RT_NumTypes; i++ )
	{
		m_resourceTypeMap.insert(std::pair<ProjectResource::ResourceTypes, std::list<ProjectResource *>>(static_cast<ProjectResource::ResourceTypes>(i), std::list<ProjectResource *>()));
	}

}



ProjectResourceManager::~ProjectResourceManager()
{
	delete m_lock;
}



void ProjectResourceManager::deserializeResources()
{
	SCOPE_LOCKER lock(getLock(), "Deserialize ResourceManager");

	for ( size_t i = 0 ; i < ProjectResource::RT_NumTypes; i++ )
	{
		std::list<ProjectResource *> res = getResourcesByType(static_cast<ProjectResource::ResourceTypes>(i));

		for ( std::list<ProjectResource *>::iterator it(res.begin()); it != res.end(); it++ )
		{
			(*it)->deserialize();
		}
	}
}



ProjectResource * ProjectResourceManager::getResourceByName(ArkString name) const
{
	if ( m_resourceMap.find(name) != m_resourceMap.end() )
	{
		return m_resourceMap.at(name);
	}

	return NULL;
}



std::list<ProjectResource *> ProjectResourceManager::getResourcesByType(ProjectResource::ResourceTypes type) const
{
	if ( m_resourceTypeMap.find(type) != m_resourceTypeMap.end() )
	{
		return m_resourceTypeMap.at(type);
	}

	return std::list<ProjectResource *>();
}



void ProjectResourceManager::onNotify(NotificationEvent const * notificationEvent)
{


	switch ( notificationEvent->getType() )
	{
	case NotificationEvent::EventType::Project_Opened:
	{
		genAndDeserializeProjectResources();
	}
	break;
	case NotificationEvent::Project_Closed:
		serializeResources();
		// TODO (AD) Clear map here
		break;
	}
}



void ProjectResourceManager::genAndDeserializeProjectResources()
{
	ArkStringList allFiles;
	genFilelist(allFiles);

	for ( size_t i = 0 ; i < allFiles.size(); i++ )
	{
		ArkString absPath(allFiles.at(i));
		ArkString resourceName(absPath.split('/').getLast());

		ProjectResource * newResource = NULL;

		ProjectResource::ResourceTypes type = ProjectResource::getResourceTypeFromExtension(resourceName.split('/').getLast().split('.').getLast());
		switch ( type )
		{
		case ProjectResource::RT_Scene:
			newResource = new Scene(resourceName, absPath);
			break;
		case ProjectResource::RT_Texture:
			newResource = new TextureResource(resourceName, absPath);
			break;
		case ProjectResource::RT_Mesh:
			newResource = new MeshResource(resourceName, absPath);
			break;
		case ProjectResource::RT_Material:
			newResource = new MaterialResource(resourceName, absPath);
			break;
		case ProjectResource::RT_Shader:
			newResource = new ShaderResource(resourceName, absPath);
			OpenGLRenderer::Instance()->getShaderFactory()->addShaderToFactory(dynamic_cast<ShaderResource const *>(newResource));
			break;
		}

		if ( newResource )
		{
			m_resourceMap.insert(std::pair<ArkString, ProjectResource *>(resourceName, newResource));
			m_resourceTypeMap.at(type).push_back(newResource);
		}
	}

	deserializeResources();
	eventSystem->fireEvent(NotificationEvent::Project_ResourcesLoaded);
}



void ProjectResourceManager::genFilelist(ArkStringList &allFiles)
{
	ArkString root(arkEngine->getProjectManager()->getProjectRoot());
	ArkDirectory dir(root);
	ArkStringList dirs = dir.getEntryList(ArkDirectory::ET_Directories);

	for ( size_t i = 0 ; i < dirs.size(); i++ )
	{
		if ( dirs.at(i) != "." )
		{
			ArkString dirpath(root + dirs.at(i));

			ArkDirectory subdir(dirpath);
			ArkStringList filelist(subdir.getEntryList(ArkDirectory::ET_Files));

			for ( size_t k = 0 ; k < filelist.size() ; k++ )
			{
				ArkString pathToFile(dirpath + "/" + filelist.at(k));
				allFiles.push_back(pathToFile);
			}
		}
	}
}



void ProjectResourceManager::serializeResources()
{
	SCOPE_LOCKER lock(getLock(), "Serialize ResourceManager");
}