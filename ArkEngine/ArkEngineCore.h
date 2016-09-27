
#pragma once

#include "VkRenderer.h"

class ArkEngineCore
{
public:
	int run()
	{
		// NOTE Maybe pass off to another thread here?
		initMemory();
		initRenderer();
		initSystem();
		startThreads();

		runMainLoop();
		return 0;
	}

	int shutdown() {
		stopThreads();
		deinitSystem();
		deinitRenderer();
		deinitMemory();

		return 0;
	}

private:
	void initMemory();
	void initRenderer();
	void initSystem();
	void startThreads();
	void runMainLoop();

	void stopThreads();
	void deinitSystem();
	void deinitRenderer();
	void deinitMemory();

private:
	VkRenderer * mRenderer;


};