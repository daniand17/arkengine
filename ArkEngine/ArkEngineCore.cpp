#include "ArkEngineCore.h"
#include "ArkString.h"
#include "ArkSize.h"
#include "ProjectManager.h"
#include "ArkConstants.h"


using namespace ArkThreading;
ArkEngineCore * ArkEngineCore::sm_instance = NULL;

ArkEngineCore::ArkEngineCore()
	: m_window(NULL)
	, m_sceneManager(NULL)
	, m_resourceManager(NULL)
	, m_projectManager(NULL)
	, m_taskQueue(NULL)
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

#ifdef USE_OPENGL
	m_renderer = new OpenGLRenderer(m_window);
	m_renderer->initializeRenderer();
#endif // USE_OPENGL

	m_sceneManager = new SceneManager();
	m_resourceManager = new ResourceManager();
	m_projectManager = new ProjectManager();
	m_taskQueue = new TaskQueue();
}



void ArkEngineCore::startThreads()
{

	for ( int i = 0 ; i < NUM_THREADS ; i++ )
	{
		m_threads.push_back(new ArkThread(m_taskQueue));
	}
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

		std::vector<Renderer *> rens = getSceneManager()->getCurrentScene()->getRenderers();
		std::vector<RendererInfo> renInfos;

		for ( std::vector<Renderer *>::const_iterator renIt(rens.begin()) ; renIt != rens.end() ; renIt++ )
		{
			Renderer * renderer(*renIt);

			renInfos.push_back(RendererInfo(
				RendererInfo::RT_Mesh,
				renderer->getMaterial(),
				renderer->getModelMatrix(),
				static_cast<MeshRenderer *>(renderer)->getMesh()
			));
		}

		m_renderer->renderScene(renInfos);

	}

	eventSystem->fireEvent(NotificationEvent::System_Shutdown);
}



void ArkEngineCore::stopThreads()
{

	for ( std::list<ArkThread *>::iterator it(m_threads.begin()) ; it != m_threads.end() ; it++ )
	{
		ArkThread * th = *it;
		th->stop();
		delete th;
	}

	m_threads.clear();
}



void ArkEngineCore::deinitMemory()
{
	delete m_sceneManager;
	delete m_renderer;
	delete m_window;
}