#include "SystemTasks.h"
#include "ArkDebug.h"
#include "Input.h"
#include "ResourceManager.h"
#include "RendererContext.h"

using namespace ArkRendering;

void SystemTask::init()
{
	Debug::Log("Initializing System task");
}

void SystemTask::run()
{
	bool done = false;
	Debug::Log("Running System Task");
	SceneManager * sceneManager = ArkEngineCore::Instance()->getSceneManager();

	if ( sceneManager )
		m_currentScene = sceneManager->getCurrentScene();

	GameObject * object = new GameObject();
	object->addComponent<MeshRenderer>();
	MeshRenderer * ren = object->getComponent<MeshRenderer>();

	MaterialInfo * material = ResourceManager::Instance()->GetMaterialFactory()->getResourceByName("DefaultMaterial");
	MeshInfo * mesh = ResourceManager::Instance()->GetMeshFactory()->getResourceByName("cube.obj");

	ren->setMaterial(material);
	ren->setMesh(mesh);

	object->instantiate(object, Vec3(0, 0, 0), Quaternion(0, 0, 0, 0));

	GameObject * obj = new GameObject();
	obj->addComponent<MeshRenderer>();
	ren = obj->getComponent<MeshRenderer>();
	ren->setMaterial(material);
	ren->setMesh(ResourceManager::Instance()->GetMeshFactory()->getResourceByName("Suzanne.obj"));

	object->instantiate(obj, Vec3::zero(), Quaternion(0, 0, 0, 0));

	
	SystemNotificationBus * bus = ArkEngineCore::Instance()->getNotificationBus();

	do
	{




		if ( m_currentScene->getSceneChanged() )
		{
			bus->fireNotify(SystemNotifications::ServiceTypes::OnSceneChanged);
			m_currentScene->setSceneChanged(false);
		}
		glfwPollEvents();
	}
	while ( !done );
}
