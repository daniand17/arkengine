#include "SystemTasks.h"
#include "ArkDebug.h"
#include "Input.h"
#include "ResourceManager.h"
#include "RendererModelManager.h"

using namespace ArkRendering;

void SystemTask::init()
{
	
}

void SystemTask::run()
{
	bool done = false;

	ResourceManager * resourceManager = ResourceManager::Instance();
	Resource_Id meshId = resourceManager->GetMeshFactory()->LoadMesh("cube.obj");
	Resource_Id materialId = resourceManager->GetMaterialFactory()->CreateMaterial();

	do
	{
		if ( Input::GetKeyDown(Input::KeyCodes::Key_W) )
		{
			if ( RendererModelManager::Instance()->GetNumModels() < 10000 )
			{
				ModelInfo * modelInfo = RendererModelManager::Instance()->GetNextModelInfoForPopulate();
				modelInfo->materialId = materialId;
				modelInfo->meshId = meshId;
				modelInfo->modelMatrix = Mat4::identity();
			}
		}
		glfwPollEvents();
	}
	while ( !done );

}
