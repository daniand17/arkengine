#include "SystemTasks.h"
#include "ArkDebug.h"
#include "Input.h"
#include "ResourceManager.h"
#include "RendererModelManager.h"

using namespace ArkRendering;

void SystemTask::init()
{
	Debug::Log("Initializing System task");
	ResourceManager * resourceManager	= ResourceManager::Instance();
	MaterialFactory * materialFactory	= resourceManager->GetMaterialFactory();
	ShaderFactory	* shaderFactory		= resourceManager->GetShaderFactory();
}

void SystemTask::run()
{
	bool done = false;
	Debug::Log("Running System Task");

	do
	{
		glfwPollEvents();
	}
	while ( !done );
}
