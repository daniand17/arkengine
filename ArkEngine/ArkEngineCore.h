#pragma once

#include "BuildOptions.h"
#include "ArkWindow.h"
#include "OpenGLRenderer.h"
#include "ArkThread.h"
#include "ResourceManager.h"

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

	ArkWindow const * GetMainWindowHandle() const { return mWindow; }


private:
	static ArkEngineCore * mInstance;

	ArkEngineCore();

	void initMemory();
	void startThreads();
	void runMainLoop();

	void stopThreads();
	void deinitMemory();

private:
	ArkWindow * mWindow;	
	ArkThreading::ArkThread * mSystemThread;

#ifdef USE_OPENGL
	OpenGLRenderer * mRenderer;
#endif // USE_OPENGL

};