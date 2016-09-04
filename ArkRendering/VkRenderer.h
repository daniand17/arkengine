#pragma once
#include <vector>
#include "Platform.h"
#include "ArkWindow.h"
class ArkWindow;
class ArkString;

class VkRenderer
{
public:
	VkRenderer();
	~VkRenderer();

	ArkWindow const * CreateArkWindow(uint32_t sizeX, uint32_t sizeY, ArkString name);

	bool Run();	// TODO Eventually move this out of this class


	int GetQueueFamilyIndex();
	VkDevice & GetDevice() { return mDevice; }
	VkQueue & GetQueue() { return mQueue; }

private:
	void initInstance();
	void deInitInstance();

	void initDevice();
	void deInitDevice();
	void getPhysicalDeviceAndProperties();

	void setupDebug();
	void initDebug();
	void deInitDebug();

private:
	VkInstance							mInstance{};
	VkPhysicalDeviceProperties			mGpuProperties{};
	VkPhysicalDevice					mGpu{};
	VkDevice							mDevice{};	// TODO make sure this goes back to private

	VkQueue								mQueue{};

	std::vector<char const *>			mInstanceLayers;
	std::vector<char const *>			mInstanceExtensions;

	std::vector<char const *>			mDeviceExtensions;

	VkDebugReportCallbackEXT			mDebugReport{};
	VkDebugReportCallbackCreateInfoEXT	mDebugCallbackCreateInfo{};

	int									mQueueFamilyIndex;

	ArkWindow * mWindow;
	

};