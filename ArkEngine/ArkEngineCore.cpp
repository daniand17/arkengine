#include "ArkEngineCore.h"

#include "ArkString.h"
#include "ArkDebug.h"

using namespace ArkThreading;
ArkEngineCore * ArkEngineCore::mInstance = NULL;

ArkEngineCore * ArkEngineCore::Instance()
{
	return mInstance;
}

void ArkEngineCore::InitEngine()
{
	mInstance = new ArkEngineCore();
}

void ArkEngineCore::initMemory()
{
	mWindow = new ArkWindow(512, 512, "Ark Engine");

#ifdef USE_OPENGL
	mRenderer = new OpenGLRenderer(mWindow);
	mRenderer->InitializeRenderer();
#endif // USE_OPENGL
}

void ArkEngineCore::startThreads()
{
	// SystemThread?
	// PhysicsThread?
}

void ArkEngineCore::runMainLoop()
{
	mRenderer->Run();
}

void ArkEngineCore::stopThreads()
{
	mRenderer->Stop();
}

void ArkEngineCore::deinitMemory()
{
	delete mRenderer;
	delete mWindow;
}