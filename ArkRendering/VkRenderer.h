#pragma once
#include <vector>
#include "Platform.h"
#include "ArkString.h"

class ArkWindow;

class VkRenderer
{
public:
	VkRenderer();
	~VkRenderer();

	ArkWindow const * CreateArkWindow(uint32_t sizeX, uint32_t sizeY, ArkString name);

	bool Run();	// TODO Eventually move this out of this class

	const int GetQueueFamilyIndex() const;
	const VkInstance 						GetVkInstance()					const { return mInstance; }
	const VkPhysicalDevice					GetVkPhysicalDevice()			const { return mGpu; }
	const VkDevice							GetVkDevice()					const { return mDevice; }
	const VkQueue							GetVkQueue()					const { return mQueue; }
	const VkPhysicalDeviceProperties &		GetVkPhysicalDeviceProperties() const { return mGpuProperties; }

private:
	void initInstance();
	void deInitInstance();

	void initDevice();
	void deInitDevice();
	void getPhysicalDeviceAndProperties();

	void setupDebug();
	void initDebug();
	void deInitDebug();

	void setupLayersAndExtensions();

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

	mutable int							mQueueFamilyIndex;

	ArkWindow * mWindow;
};