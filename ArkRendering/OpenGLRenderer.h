#pragma once
#include "BuildOptions.h"
#include "ArkWindow.h"

#ifdef USE_OPENGL
class OpenGLRenderer
{

public:
	OpenGLRenderer(ArkWindow * windowHandle);
	OpenGLRenderer(size_t sizeX, size_t sizeY);
	~OpenGLRenderer();
	void start();
	void stop() { mShouldRun = false; }

private:
	GLFWwindow * mWindow;
	bool mShouldRun;
	size_t mSizeX;
	size_t mSizeY;
};
#endif
