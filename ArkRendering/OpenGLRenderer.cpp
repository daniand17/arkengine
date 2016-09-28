#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer(ArkWindow * windowHandle)
{
	mWindow = windowHandle->getOSWindowHandle();
}

OpenGLRenderer::OpenGLRenderer(size_t sizeX, size_t sizeY)
	: mShouldRun(false)
	, mSizeX(sizeX)
	, mSizeY(sizeY)
{
}

OpenGLRenderer::~OpenGLRenderer()
{
}

void OpenGLRenderer::start()
{
	std::move(mWindow);
	mShouldRun = true;
	do
	{
		glfwSwapBuffers(mWindow); // TODO (AD) move to a rendering thread?
		glfwPollEvents(); // TODO (AD) move to a system thread?
	}
	while ( mShouldRun || glfwGetKey(mWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(mWindow));
}
