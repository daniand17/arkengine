#pragma once
#include <thread>

#include "BuildOptions.h"
#include "ArkWindow.h"
#include "OpenGLRenderer.h"

class ArkEngineCore
{
public:
	int run()
	{
		// NOTE Maybe pass off to another thread here?
		initMemory();
		initSystem();
		startThreads();

		runMainLoop();
		return 0;
	}

	int shutdown()
	{
		stopThreads();
		deinitSystem();
		deinitMemory();

		return 0;
	}

private:
	void initMemory();
	void initSystem();
	void startThreads();
	void runMainLoop();

	void stopThreads();
	void deinitSystem();
	void deinitMemory();

private:
	ArkWindow * mWindow;	

#ifdef USE_OPENGL
	OpenGLRenderer * mRenderer;
#endif // USE_OPENGL
	std::thread * mRenderThread;


};