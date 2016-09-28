#include <stdint.h>

#include "ArkWindow.h"


ArkWindow::ArkWindow(unsigned int sizeX, unsigned int sizeY, ArkString windowName) :
	mWindowShouldRun(true),
	mSizeX(sizeX),
	mSizeY(sizeY),
	mWindowName(windowName)
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
