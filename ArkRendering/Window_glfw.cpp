
#include "ArkWindow.h"

void ArkWindow::initOSWindow()
{
	if ( !glfwInit() )
		fprintf(stderr, "Failed to initialize GLFW\n");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow	= glfwCreateWindow(mSizeX, mSizeY, mWindowName.toStdString().c_str(), NULL, NULL);

	if ( !mWindow)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
	}

	glfwMakeContextCurrent(mWindow);
	glewExperimental = true;
	if ( glewInit() != GLEW_OK )
		fprintf(stderr, "Failed to initialize GLEW.\n");

	glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE);
}

void ArkWindow::deInitOSWindow()
{
}

void ArkWindow::updateOSWindow()
{
}