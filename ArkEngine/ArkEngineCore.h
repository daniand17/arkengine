#pragma once

#include "BuildOptions.h"
#include "ArkWindow.h"
#include "OpenGLRenderer.h"

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

private:
	static ArkEngineCore * mInstance;

	ArkEngineCore() {}
	void initMemory();
	void startThreads();
	void runMainLoop();

	void stopThreads();
	void deinitMemory();

private:
	ArkWindow * mWindow;	

#ifdef USE_OPENGL
	OpenGLRenderer * mRenderer;
#endif // USE_OPENGL

};