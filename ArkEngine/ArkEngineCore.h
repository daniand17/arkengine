#pragma once

#include "BuildOptions.h"
#include "ArkWindow.h"
#include "OpenGLRenderer.h"
#include "ArkThread.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SystemNotifications.h"

class ProjectManager;

#define arkEngine ArkEngineCore::Instance()

class ArkEngineCore
{
public:
	static ArkEngineCore * Instance() { return sm_instance; }
	static void InitEngine();
	int run();
	

	int shutdown()
	{
		stopThreads();
		deinitMemory();
		return 0;
	}

	ArkWindow const * GetMainWindowHandle() const { return m_window; }

	SceneManager * getSceneManager() const { return m_sceneManager; }
	ResourceManager * getResourceManager() const { return m_resourceManager; }
	RendererContext * getRendererContext() const { return m_rendererContext; }
	ProjectManager * getProjectManager() const { return m_projectManager; }


private:
	static ArkEngineCore * sm_instance;

	ArkEngineCore();

	void initMemory();
	void startThreads();
	void runMainLoop();

	void stopThreads();
	void deinitMemory();

private:
	ArkWindow * m_window;
	ArkThreading::ArkThread * m_systemThread;

	SceneManager * m_sceneManager;

	ResourceManager * m_resourceManager;
	RendererContext * m_rendererContext;
	ProjectManager * m_projectManager;


#ifdef USE_OPENGL
	OpenGLRenderer * m_renderer;
#endif // USE_OPENGL
};