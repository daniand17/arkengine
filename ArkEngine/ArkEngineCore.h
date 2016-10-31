#pragma once

#include "BuildOptions.h"
#include "ArkWindow.h"
#include "OpenGLRenderer.h"
#include "ArkThread.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SystemNotifications.h"
#include "SceneToRendererSynchronizer.h"

class SceneToRendererSynchronizer;

class ArkEngineCore
{
public:
	static ArkEngineCore * Instance();
	static void InitEngine();
	int Run()
	{
		initMemory();
		startThreads();

		runMainLoop();
		return 0;
	}

	int Shutdown()
	{
		stopThreads();
		deinitMemory();

		return 0;
	}

	ArkWindow const * GetMainWindowHandle() const { return m_window; }

	SceneManager * getSceneManager() const { return m_sceneManager; }
	SystemNotificationBus * getNotificationBus() const { return m_notificationBus; }


private:
	static ArkEngineCore * sm_instance;

	ArkEngineCore();

	void initMemory();
	void startThreads();
	void runMainLoop();

	void stopThreads();
	void deinitMemory();

private:
	ArkWindow * m_window;	
	ArkThreading::ArkThread * m_systemThread;

	SceneManager * m_sceneManager;
	SystemNotificationBus * m_notificationBus;
	SceneToRendererSynchronizer * m_sceneToRendererSynchronizer;

#ifdef USE_OPENGL
	OpenGLRenderer * m_renderer;
#endif // USE_OPENGL
};