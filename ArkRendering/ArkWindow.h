#pragma once
#include "BuildOptions.h"
#include "ArkString.h"
#include "ArkSize.h"

class ArkWindow
{
public:
	ArkWindow(ArkSize windowSize, ArkString windowName);
	ArkWindow(unsigned int sizeX, unsigned int sizeY, ArkString windowName);
	~ArkWindow();

	void Close();
	bool Update();
	ArkSize size() const { return mSize; }
	float aspectRatio() const { return (float) mSize.width() / (float) mSize.height(); }

private:
	bool mWindowShouldRun;

	ArkString mWindowName;

	ArkSize mSize;

	void initOSWindow();
	void deInitOSWindow();
	void updateOSWindow();

#ifdef  USE_OPENGL
	GLFWwindow * mWindow;
public:
	GLFWwindow * getOSWindowHandle() const { return mWindow; }
#endif //  USE_OPENGL

#if VK_USE_PLATFORM_WIN32_KHR
	HINSTANCE _win32_instance	= NULL;
	HWND		_win32_window	= NULL;
	
	std::string _win32_class_name;
	static uint64_t _win32_class_id_counter;
#endif
};