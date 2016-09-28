#include "ArkEngineCore.h"

#include "ArkString.h"
#include "ArkDebug.h"

using namespace ArkThreading;

void ArkEngineCore::initMemory()
{
	mWindow = new ArkWindow(512, 512, "Ark Engine");

#ifdef USE_OPENGL
	mRenderer = new OpenGLRenderer(mWindow);
#endif // USE_OPENGL
}

void ArkEngineCore::initSystem()
{
	// TODO (AD) Initialize other system stuff here
}

void ArkEngineCore::startThreads()
{
	mRenderThread = new ArkThread(mRenderer);
	
	// SystemThread
	// PhysicsThread

}

void ArkEngineCore::runMainLoop()
{
}

void ArkEngineCore::stopThreads()
{
	mRenderThread->join();
}

void ArkEngineCore::deinitSystem()
{
}

void ArkEngineCore::deinitMemory()
{
	delete mRenderer;
}