#include "ArkEngineCore.h"
#include "RendererModelManager.h"
#include "ArkString.h"
#include "ArkSize.h"
#include "SystemTasks.h"
#include "ProjectManager.h"

using namespace ArkThreading;
ArkEngineCore * ArkEngineCore::mInstance = NULL;

ArkEngineCore::ArkEngineCore()
{
	initMemory();
}

ArkEngineCore * ArkEngineCore::Instance()
{
	return mInstance;
}

void ArkEngineCore::InitEngine()
{
	mInstance = new ArkEngineCore();
}

void ArkEngineCore::initMemory()
{
	
	mWindow = new ArkWindow(ArkSize(1024, 768), "Ark Engine");
	mSystemThread = new ArkThread(new SystemTask());

#ifdef USE_OPENGL
	mRenderer = new OpenGLRenderer(mWindow);
	mRenderer->InitializeRenderer();
#endif // USE_OPENGL

	ResourceManager::Initialize();
	RendererModelManager::Initialize();
	ProjectManager::Initialize();
	ProjectManager::Instance()->createNewProjectWithName("DefaultProject");
}

void ArkEngineCore::startThreads()
{
	mSystemThread->init();
	// PhysicsThread?
}

void ArkEngineCore::runMainLoop()
{
	mRenderer->Run();
}

void ArkEngineCore::stopThreads()
{
	mRenderer->Stop();
}

void ArkEngineCore::deinitMemory()
{
	ProjectManager::Instance()->closeCurrentProject();

	delete mRenderer;
	delete mWindow;
}