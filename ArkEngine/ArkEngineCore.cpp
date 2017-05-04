#include "ArkEngineCore.h"
#include "RendererContext.h"
#include "ArkString.h"
#include "ArkSize.h"
#include "SystemTasks.h"
#include "ProjectManager.h"
#include "SystemThread.h"

using namespace ArkThreading;
ArkEngineCore * ArkEngineCore::sm_instance = NULL;

ArkEngineCore::ArkEngineCore()
	: m_window(NULL)
	, m_systemThread(NULL)
	, m_sceneManager(NULL)
	, m_resourceManager(NULL)
	, m_rendererContext(NULL)
	, m_projectManager(NULL)
{
}



void ArkEngineCore::InitEngine()
{
	sm_instance = new ArkEngineCore();
	SystemNotificationBus::Initialize();
}

int ArkEngineCore::run()
{
	initMemory();
	startThreads();

	runMainLoop();
	return 0;
}



void ArkEngineCore::initMemory()
{
	m_window = new ArkWindow(ArkSize(1024, 768), "Ark Engine");
	m_systemThread = new SystemThread();

#ifdef USE_OPENGL
	m_renderer = new OpenGLRenderer(m_window);
	m_renderer->initializeRenderer();
#endif // USE_OPENGL

	m_sceneManager = new SceneManager();
	m_resourceManager = new ResourceManager();
	m_rendererContext = new RendererContext();
	m_projectManager = new ProjectManager();
}



void ArkEngineCore::startThreads()
{
	m_systemThread->start();
	// PhysicsThread?
}



void ArkEngineCore::runMainLoop()
{
	eventSystem->fireEvent(NotificationEvent::System_Startup);



	while ( 1 )
	{
		// do physics

		eventSystem->fireEvent(NotificationEvent::Tick_FixedUpdate);



		// do other updates 

		eventSystem->fireEvent(NotificationEvent::Tick_Update);

		m_renderer->renderScene();
	}
	
	
	eventSystem->fireEvent(NotificationEvent::System_Shutdown);
}



void ArkEngineCore::stopThreads()
{
	m_systemThread->join();
	m_renderer->stop();
}



void ArkEngineCore::deinitMemory()
{
	delete m_sceneManager;
	delete m_renderer;
	delete m_systemThread;
	delete m_window;
}