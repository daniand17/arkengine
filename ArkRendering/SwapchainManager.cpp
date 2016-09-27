#include <set>

#include "SwapchainManager.h"
#include "Shared.h"

SwapchainManager::SwapchainManager(VkRenderer const * renderer)
	: mRenderer(renderer)
{
}

SwapchainManager::~SwapchainManager() {}

void SwapchainManager::init(VkSurfaceKHR const & surface)
{
	mSurface = surface;
	SwapchainSupportDetails swapchainSupport = querySwapchainSupport(mRenderer->GetVkPhysicalDevice());

	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapchainSupport.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapchainSupport.presentModes);
	VkExtent2D extent = chooseSwapExtent(swapchainSupport.capabilities);

	uint32_t imageCount = swapchainSupport.capabilities.minImageCount + 1;

	if ( swapchainSupport.capabilities.maxImageCount > 0 && imageCount > swapchainSupport.capabilities.maxImageCount )
		imageCount = swapchainSupport.capabilities.maxImageCount;

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = mSurface;
	createInfo.minImageCount = imageCount;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;	// always 1 unless doing stereoscopic
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	mRenderer->GetQueueFamilyIndex();

}

bool SwapchainManager::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, NULL);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(mDeviceExtensions.begin(), mDeviceExtensions.end());

	for ( const auto & extension : availableExtensions )
		requiredExtensions.erase(extension.extensionName);

	return requiredExtensions.empty();
}

bool SwapchainManager::isDeviceSuitable(VkPhysicalDevice device)
{
	bool swapchainAdequate = false;
	if ( checkDeviceExtensionSupport(device) )
	{
		SwapchainSupportDetails details = querySwapchainSupport(device);

		swapchainAdequate = !details.formats.empty() && !details.presentModes.empty();
	}

	return swapchainAdequate;
}

SwapchainManager::SwapchainSupportDetails SwapchainManager::querySwapchainSupport(VkPhysicalDevice device)
{
	SwapchainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, mSurface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, mSurface, &formatCount, NULL);

	if ( formatCount != 0 )
	{
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, mSurface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, mSurface, &presentModeCount, NULL);

	if ( presentModeCount != 0 )
	{
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, mSurface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

VkSurfaceFormatKHR SwapchainManager::chooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> const & availableFormats)
{
	if ( availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED )
	{
		return{VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
	}

	for ( const auto & availableFormat : availableFormats )
	{
		if ( availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR )
			return availableFormat;
	}

	return availableFormats[0];
}

VkPresentModeKHR SwapchainManager::chooseSwapPresentMode(std::vector<VkPresentModeKHR> const availablePresentModes)
{
	for ( const auto & availableMode : availablePresentModes )
	{
		if ( availableMode == VK_PRESENT_MODE_MAILBOX_KHR )
			return availableMode;
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapchainManager::chooseSwapExtent(VkSurfaceCapabilitiesKHR const & capabilities)
{
	if ( capabilities.currentExtent.width != UINT32_MAX )
	{
		return capabilities.currentExtent;
	}
	else
	{

		VkExtent2D actualExtent = {512, 512};	// TODO (AD) this might be wrong

		actualExtent.width = max(capabilities.minImageExtent.width, min(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = max(capabilities.minImageExtent.height, min(capabilities.maxImageExtent.height, actualExtent.height));

		return actualExtent;
	}
}

