#pragma once

#include "BuildOptions.h"
#include "ArkWindow.h"
#include "OpenGLRenderer.h"
#include "ArkThread.h"
#include "ResourceManager.h"
#include "SceneManager.h"

class ArkEngineCore
{
public:
	static ArkEngineCore * Instance();
	static void InitEngine();
	int Run()
	{
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


private:
	static ArkEngineCore * mInstance;

	ArkEngineCore();

	void initMemory();
	void startThreads();
	void runMainLoop();

	void stopThreads();
	void deinitMemory();

private:
	ArkWindow * m_window;	
	ArkThreading::ArkThread * mSystemThread;

	SceneManager * m_sceneManager;

#ifdef USE_OPENGL
	OpenGLRenderer * m_renderer;
#endif // USE_OPENGL
};