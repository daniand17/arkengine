#include "ArkEngineCore.h"

#include "ArkString.h"
#include "ArkDebug.h"
#include "ArkSize.h"

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
	mWindow = new ArkWindow(ArkSize(1024, 768), "Ark Engine");

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