#include "ArkEngineCore.h"

#include "ArkString.h"
#include "ArkDebug.h"

void ArkEngineCore::initMemory()
{
	Debug::Log("Initializing memory");
	mWindow = new ArkWindow(512, 512, "Ark Engine");

#ifdef USE_OPENGL
	Debug::Log("Initializing OpenGL renderer");
	mRenderer = new OpenGLRenderer(mWindow);
	Debug::Log("OpenGL renderer initialization complete");
#endif // USE_OPENGL
	Debug::Log("Memory initialization complete");
}

void ArkEngineCore::initSystem()
{
	Debug::Log("Initializing system");
	// TODO (AD) Initialize other system stuff here
	Debug::Log("System initialization complete");
}

void ArkEngineCore::startThreads()
{
	// TODO start other threads and pass ownership of each part to them:
	Debug::Log("Initializing threads");
	// RenderThread
	
	// SystemThread
	// PhysicsThread

	Debug::Log("Thread initialization complete");
}

void ArkEngineCore::runMainLoop()
{
	while ( 1 )
	{
	}
}

void ArkEngineCore::stopThreads()
{
	mRenderer->stop();
}

void ArkEngineCore::deinitSystem()
{
}

void ArkEngineCore::deinitMemory()
{
	delete mRenderer;
}