#pragma once
#include <vector>

#include "ArkString.h"
#include "VkRenderer.h"
#include "SwapchainManager.h"

class ArkWindow
{
public:
	ArkWindow(VkRenderer * renderer, uint32_t sizeX, uint32_t sizeY, ArkString name);
	~ArkWindow();

	void Close();
	bool Update();

private:	// Functions
	void initOSWindow();
	void deInitOSWindow();
	void updateOSWindow();
	void initOSSurface();

	void initSurface();
	void deInitSurface();

private:
	bool mWindowShouldRun;

	ArkString mWindowName;

	uint32_t mSizeX;
	uint32_t mSizeY;
	uint32_t mSwapchainImageCount;

	VkRenderer *				mRenderer;
	VkSurfaceKHR				mSurface;

	VkSurfaceCapabilitiesKHR	mSurfaceCapabilities{};
	VkSurfaceFormatKHR			mSurfaceFormat{};

	SwapchainManager mSwapchainManager;

#if VK_USE_PLATFORM_WIN32_KHR
	HINSTANCE _win32_instance = NULL;
	HWND		_win32_window = NULL;

	std::string _win32_class_name;
	static uint64_t _win32_class_id_counter;
#endif
};