#pragma once
#include <vector>
#include <map>

#include "BuildOptions.h"
#include "ArkWindow.h"
#include "ArkThread.h"
#include "ArkRendering.h"
#include "BufferData.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Camera.h"
#include "RendererInfo.h"


#ifdef USE_OPENGL
class OpenGLRenderer
{
public:
	ArkWindow const * GetWindowHandle() const { return m_arkWindow; }
	OpenGLRenderer(ArkWindow * windowHandle);
	OpenGLRenderer::~OpenGLRenderer() { shutdownRenderer(); }

	void shutdownRenderer();
	void initializeRenderer();
	void renderScene(std::vector<RendererInfo> & renderers);

private:
	ArkWindow *	m_arkWindow;
	GLuint	mVertexArrayId;

private:
	void clearScreen();

};
#endif