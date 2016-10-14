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

	ArkRendering::ShaderProgram	* mShaderProgram;
	BufferData<Vec3> mVertexBuffer;
	BufferData<Vec2> mUvBuffer;
	BufferData<Vec3> mNormalBuffer;

	size_t mNumModelsInLastBuffer;

	void updateBuffers();
};
#endif