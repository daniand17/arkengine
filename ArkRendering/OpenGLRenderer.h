#pragma once
#include <vector>

#include "BuildOptions.h"
#include "ArkWindow.h"
#include "ArkThread.h"
#include "ArkRendering.h"
#include "BufferData.h"
#include "Vec2.h"
#include "Vec3.h"

#ifdef USE_OPENGL
class OpenGLRenderer
{
public:
	static OpenGLRenderer const * Instance() { return mInstance; }
	ArkWindow const * GetWindowHandle() const { return mWindow; }
	OpenGLRenderer(ArkWindow * windowHandle);
	OpenGLRenderer();
	~OpenGLRenderer();
	void Stop() { mShouldRun = false; }
	void DeinitRenderer();
	void InitializeRenderer();
	void Run();

private:
	static OpenGLRenderer * mInstance;
	ArkWindow *	mWindow;
	bool	mShouldRun;
	GLuint	mVertexArrayId;

	BufferCache mBufferCache;
	size_t mNumModelsInLastBuffer;

	void updateBuffers();
};
#endif