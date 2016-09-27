#include <iostream>

#include "ArkEngineCore.h"
#include "ArkString.h"
#include "ArkDebug.h"
void ArkEngineCore::initMemory()
{
	Debug::Log("Initializing memory");
	// TODO (AD) Initialize memory here
	Debug::Log("Memory initialization complete");
}

void ArkEngineCore::initRenderer()
{
	Debug::Log("Initializing Vulkan renderer");
	mRenderer = new VkRenderer();
	mRenderer->CreateArkWindow(512, 512, "New Ark Window");
	Debug::Log("Vulkan renderer initialization complete");
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

	// TODO (AD) Initialize memory here
	Debug::Log("Thread initialization complete");
}

void ArkEngineCore::runMainLoop()
{	
	while ( mRenderer->Run() );
}

void ArkEngineCore::stopThreads()
{
}

void ArkEngineCore::deinitSystem()
{
}

void ArkEngineCore::deinitRenderer()
{
	delete mRenderer;
}

void ArkEngineCore::deinitMemory()
{
}
