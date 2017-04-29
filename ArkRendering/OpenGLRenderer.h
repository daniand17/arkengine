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
#include "RenderState.h"
#include "Camera.h"
class RendererContext;

#ifdef USE_OPENGL
class OpenGLRenderer
{
public:
	ArkWindow const * GetWindowHandle() const { return m_arkWindow; }
	OpenGLRenderer(ArkWindow * windowHandle);
	OpenGLRenderer::~OpenGLRenderer() { shutdownRenderer(); }

	OpenGLRenderer();

	void stop() { m_shouldRun = false; }
	void shutdownRenderer();
	void initializeRenderer();
	void run();
	void setRenderContext(RendererContext * rendererContext) { m_rendererContext = rendererContext; }

private:
	ArkWindow *	m_arkWindow;
	bool	m_shouldRun;
	GLuint	mVertexArrayId;

	std::vector<RenderState *> mRenderStateList;

	typedef std::map<ArkString, BufferSet *> BufferCollection;
	typedef std::pair<ArkString, BufferSet *> BufferMaterialNamePair;
	BufferCollection mBufferSetMap;
	RendererContext * m_rendererContext;


private:
	void clearScreen();

};
#endif