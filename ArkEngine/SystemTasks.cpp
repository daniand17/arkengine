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

	object->instantiate(object, Vec3(0, 0, 0), Quaternion(0, 0, 0, 0));

	GameObject * obj = new GameObject();
	obj->addComponent<MeshRenderer>();
	ren = obj->getComponent<MeshRenderer>();

	object->instantiate(obj, Vec3::zero(), Quaternion(0, 0, 0, 0));

	
	do
	{
		if ( m_currentScene->getSceneChanged() )
		{
			eventSystem->fireEvent(NotificationEvent::System_SceneChanged);
			m_currentScene->setSceneChanged(false);
		}
		glfwPollEvents();
	}
	while ( !done );
}
