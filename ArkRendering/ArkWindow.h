#pragma once

#include "VkRenderer.h"
#include "ArkString.h"
class ArkWindow
{
public:
	ArkWindow();
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
	void initOSSurface();


#if VK_USE_PLATFORM_WIN32_KHR
	HINSTANCE _win32_instance	= NULL;
	HWND		_win32_window	= NULL;
	
	std::string _win32_class_name;
	static uint64_t _win32_class_id_counter;
#endif
};