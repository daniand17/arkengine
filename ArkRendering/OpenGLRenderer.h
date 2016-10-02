#pragma once
#include "BuildOptions.h"
#include "ArkWindow.h"
#include "ArkThread.h"

#ifdef USE_OPENGL
class OpenGLRenderer
{
public:
	OpenGLRenderer(ArkWindow * windowHandle);
	OpenGLRenderer();
	~OpenGLRenderer();
	void Stop() { mShouldRun = false; }
	void InitializeRenderer();
	void Run();

private:
	ArkWindow * mWindow;
	bool mShouldRun;
	GLuint mProgramID;
	GLuint mVertexBuffer;
};
#endif
