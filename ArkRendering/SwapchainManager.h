#include <vector>

#include "VkRenderer.h"

class SwapchainManager
{
public:
	SwapchainManager(VkRenderer const * renderer);
	~SwapchainManager();
	void init(VkSurfaceKHR const & surface);

	struct SwapchainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

private:

	const std::vector<const char *> mDeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	VkRenderer const * mRenderer;
	VkSurfaceKHR mSurface;

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);

	SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> const & availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(std::vector<VkPresentModeKHR> const availablePresentModes);

	VkExtent2D chooseSwapExtent(VkSurfaceCapabilitiesKHR const & capabilities);

};