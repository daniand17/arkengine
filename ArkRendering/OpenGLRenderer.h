#pragma once
#include "BuildOptions.h"
#include "ArkWindow.h"
#include "ArkThread.h"

#ifdef USE_OPENGL
class OpenGLRenderer : public ArkThreading::WorkerTask
{
public:
	OpenGLRenderer(ArkWindow * windowHandle);
	OpenGLRenderer(size_t sizeX, size_t sizeY);
	~OpenGLRenderer();
	void stop() { mShouldRun = false; }

protected:
	void init();
	void run();

private:
	GLFWwindow * mWindow;
	bool mShouldRun;
	size_t mSizeX;
	size_t mSizeY;
};
#endif
