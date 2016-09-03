#pragma once
#include <vector>
#include <vulkan.h>

class VkRenderer
{
public:
	VkRenderer();
	~VkRenderer();
	int getFamilyIndex();
private:
	void _initInstance();
	void _deInitInstance();

	void _initDevice();
	void _deInitDevice();
	void _getPhysicalDeviceAndProperties();

	void _setupDebug();
	void _initDebug();
	void _deInitDebug();

private:
	VkInstance					mInstance{};
	VkPhysicalDeviceProperties	mGpuProperties{};
	VkPhysicalDevice			mGpu{};
	VkDevice					mDevice{};	// TODO make sure this goes back to private

	std::vector<char const *>	mInstanceLayers;
	std::vector<char const *>	mInstanceExtensions;

	std::vector<char const *>	mDeviceExtensions;

	VkDebugReportCallbackEXT	mDebugReport{};
	VkDebugReportCallbackCreateInfoEXT mDebugCallbackCreateInfo{};

};