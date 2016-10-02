#include <stdint.h>

#include "ArkWindow.h"


ArkWindow::ArkWindow(ArkSize windowSize, ArkString windowName) : mSize(windowSize), mWindowName(windowName)
{
	initOSWindow();
}

ArkWindow::ArkWindow(unsigned int sizeX, unsigned int sizeY, ArkString windowName) :
	mWindowShouldRun(true)
	, mSize(sizeX, sizeY)
	, mWindowName(windowName)
{
	initOSWindow();
}

ArkWindow::~ArkWindow()
{
	deInitOSWindow();
}

void ArkWindow::Close()
{
	mWindowShouldRun = false;
}

bool ArkWindow::Update()
{
	return mWindowShouldRun;
}
