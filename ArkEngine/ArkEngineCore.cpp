#include "ArkEngineCore.h"
#include "RendererContext.h"
#include "ArkString.h"
#include "ArkSize.h"
#include "SystemTasks.h"
#include "ProjectManager.h"

using namespace ArkThreading;
ArkEngineCore * ArkEngineCore::sm_instance = NULL;

ArkEngineCore::ArkEngineCore()
{
	initMemory();
}

ArkEngineCore * ArkEngineCore::Instance()
{
	return sm_instance;
}

void ArkEngineCore::InitEngine()
{
	sm_instance = new ArkEngineCore();
}

void ArkEngineCore::initMemory()
{
	m_window = new ArkWindow(ArkSize(1024, 768), "Ark Engine");
	m_systemThread = new ArkThread(new SystemTask());

#ifdef USE_OPENGL
	m_renderer = new OpenGLRenderer(m_window);
	m_renderer->InitializeRenderer();
#endif // USE_OPENGL

	m_sceneManager = new SceneManager();
	m_notificationBus = new SystemNotificationBus();

	ResourceManager::Initialize();
	RendererContext::Initialize();
	ProjectManager::Initialize();
}

void ArkEngineCore::startThreads()
{
	ProjectManager::Instance()->createNewProjectWithName("DefaultProject");
	m_sceneManager->openSceneByName("New Scene");	// TODO (AD) eventually open last scene open

	m_systemThread->init();
	// PhysicsThread?
}

void ArkEngineCore::runMainLoop()
{
	m_renderer->Run();
}

void ArkEngineCore::stopThreads()
{
	m_systemThread->join();
	m_renderer->Stop();
}

void ArkEngineCore::deinitMemory()
{
	ProjectManager::Instance()->closeCurrentProject();

	delete m_notificationBus;
	delete m_sceneManager;

	delete m_renderer;
	delete m_systemThread;
	delete m_window;
}