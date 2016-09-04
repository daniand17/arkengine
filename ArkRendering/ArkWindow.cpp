#include "ArkWindow.h"

ArkWindow::ArkWindow() :
	mWindowShouldRun(true),
	mSizeX(512),
	mSizeY(512),
	mWindowName("New Ark Window")
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
