#pragma once
#include "BuildOptions.h"

#ifdef USE_OPENGL

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#elif USE_VULKAN
#endif // BUILD_ENABLE_OPENGL

#include "ArkString.h"
class ArkWindow
{
public:
	ArkWindow(unsigned int sizeX, unsigned int sizeY, ArkString windowName);
	~ArkWindow();

	void Close();
	bool Update();

private:
	bool mWindowShouldRun;

	ArkString mWindowName;

	uint32_t mSizeX;
	uint32_t mSizeY;

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