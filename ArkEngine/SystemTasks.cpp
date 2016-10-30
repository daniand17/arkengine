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

	MaterialInfo * material = ResourceManager::Instance()->GetMaterialFactory()->getResourceByName("DefaultMaterial");
	MeshInfo * mesh = ResourceManager::Instance()->GetMeshFactory()->getResourceByName("rock.obj");

	GameObject * object = new GameObject();
	object->addComponent<MeshRenderer>();
	MeshRenderer * ren = object->getComponent<MeshRenderer>();
	ren->setMaterial(material);
	ren->setMesh(mesh);

	object->instantiate(object, Vec3(0, 0, 0), Quaternion(0, 0, 0, 0));

	do
	{
		glfwPollEvents();
	}
	while ( !done );
}
