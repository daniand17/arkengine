#pragma once
#include <vector>

#include "BuildOptions.h"
#include "ArkWindow.h"
#include "ArkThread.h"
#include "OglGlobals.h"

#ifdef USE_OPENGL
class OpenGLRenderer
{
public:
	OpenGLRenderer(ArkWindow * windowHandle);
	OpenGLRenderer();
	~OpenGLRenderer();
	void Stop() { mShouldRun = false; }
	void DeinitRenderer();
	void InitializeRenderer();
	void Run();

private:
	ArkWindow *	mWindow;
	bool	mShouldRun;
	GLuint	mVertexBufferId;
	GLuint	mVertexArrayId;

	GLuint	mUvBufferId;
	RendererUtils::ArkShaderProgram	* mShaderProgram;
};
#endif
