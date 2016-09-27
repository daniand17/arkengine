#include <cstdlib>
#include <assert.h>
#include <vector>
#include <iostream>
#include <sstream>

#include "VkRenderer.h"
#include "BuildOptions.h"
#include "Shared.h"
#include "ArkGlobals.h"
#include "ArkWindow.h"

using namespace ArkConstants;

VkRenderer::VkRenderer() :
	mQueueFamilyIndex(DATA_NONE),
	mWindow(NULL)
{
	setupLayersAndExtensions();
	setupDebug();
	initInstance();
	initDebug();
	initDevice();
}

VkRenderer::~VkRenderer()
{
	mWindow->Close();
	deInitDevice();
	deInitDebug();
	deInitInstance();
	delete mWindow;
}

ArkWindow const * VkRenderer::CreateArkWindow(uint32_t sizeX, uint32_t sizeY, ArkString name)
{
	mWindow = new ArkWindow(this, sizeX, sizeY, name);
	return mWindow;
}

void VkRenderer::initInstance()
{
	VkApplicationInfo applicationInfo{};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.apiVersion = VK_MAKE_VERSION(1, 0, 24);	// NOTE Set vk version here
	applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	applicationInfo.pApplicationName = "Ark Engine 0.1.0";

	VkInstanceCreateInfo instanceCreateInfo{};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &applicationInfo;
	instanceCreateInfo.enabledLayerCount = mInstanceLayers.size();
	instanceCreateInfo.ppEnabledLayerNames = mInstanceLayers.data();
	instanceCreateInfo.enabledExtensionCount = mInstanceExtensions.size();
	instanceCreateInfo.ppEnabledExtensionNames = mInstanceExtensions.data();
	instanceCreateInfo.pNext = &mDebugCallbackCreateInfo;

	ErrorCheck(vkCreateInstance(&instanceCreateInfo, NULL /* TODO Memory alloc stuff */, &mInstance));
}

void VkRenderer::deInitInstance()
{
	vkDestroyInstance(mInstance, NULL /* TODO Memory management for VkRenderer::_DeInit*/);
	mInstance = NULL;
}

void VkRenderer::initDevice()
{
	getPhysicalDeviceAndProperties();

	{	// Instance
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, NULL);
		std::vector<VkLayerProperties> layerPropertyList(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, layerPropertyList.data());
	}

	{	// Device
		uint32_t layerCount;
		vkEnumerateDeviceLayerProperties(mGpu, &layerCount, NULL);
		std::vector<VkLayerProperties> layerPropertyList(layerCount);
		vkEnumerateDeviceLayerProperties(mGpu, &layerCount, layerPropertyList.data());
	}

	// Queue
	float queuePriorities[]{1.0f};
	VkDeviceQueueCreateInfo deviceQueueCreateInfo{};
	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.queueFamilyIndex = GetQueueFamilyIndex();	// which type of queue family we are going to use (can ask the GPU)
	deviceQueueCreateInfo.queueCount = 1;
	deviceQueueCreateInfo.pQueuePriorities = queuePriorities;	// Tell vk driver which queue takes priority (how much compute time per queue)

	// Device
	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
	deviceCreateInfo.enabledExtensionCount = mDeviceExtensions.size();
	deviceCreateInfo.ppEnabledExtensionNames = mDeviceExtensions.data();

	ErrorCheck(vkCreateDevice(mGpu, &deviceCreateInfo, nullptr /*TODO memory allocator*/, &mDevice));

	vkGetDeviceQueue(mDevice, GetQueueFamilyIndex(), 0, &mQueue);
}

bool VkRenderer::Run()
{
	if ( mWindow )
		return mWindow->Update();
	
	return true;
}

const int VkRenderer::GetQueueFamilyIndex() const
{
	if ( mQueueFamilyIndex == DATA_NONE)
	{

		uint32_t familyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(mGpu, &familyCount, NULL);
		std::vector<VkQueueFamilyProperties> familyPropertyList(familyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(mGpu, &familyCount, familyPropertyList.data());

		bool found = false;
		for ( uint32_t i = 0; i < familyCount ; i++ )
			if ( familyPropertyList[i].queueFlags & VK_QUEUE_GRAPHICS_BIT )
			{
				mQueueFamilyIndex = i;
				return mQueueFamilyIndex;
			}

		if ( !found )
		{
			assert(0 && "Vulkan ERROR: Queue family supporting graphics not found.");
			std::exit(ARK_ERR);	// TODO maybe do something else with exiting?
		}
	}
	else
		return mQueueFamilyIndex;

	return DATA_NONE;
}

void VkRenderer::getPhysicalDeviceAndProperties()
{
	uint32_t gpuCount = 0;
	vkEnumeratePhysicalDevices(mInstance, &gpuCount, NULL);
	std::vector<VkPhysicalDevice> gpuList(gpuCount);
	vkEnumeratePhysicalDevices(mInstance, &gpuCount, gpuList.data());	// on second pass, populates the list of all the handles of all the gpus
	mGpu = gpuList[0];	// TODO assumes the first in the list is the best one, improve selection
	vkGetPhysicalDeviceProperties(mGpu, &mGpuProperties);
}

void VkRenderer::deInitDevice()
{
	vkDestroyDevice(mDevice, NULL /* TODO memory management */);
	mDevice = NULL;
}

#if BUILD_ENABLE_VULKAN_DEBUG

VKAPI_ATTR VkBool32 VKAPI_CALL
VulkanDebugCallback(
	VkDebugReportFlagsEXT		flags,
	VkDebugReportObjectTypeEXT	objType,
	uint64_t					srcObj,			// The pointer to the object
	size_t						location,		// the line where the error occurred? 
	int32_t						msgCode,		// related to flags
	char const *				layerPrefix,	// Which layer called this callback (human readable string)
	char const *				msg,			// No info so far
	void *						userData)		// No info so far
{

	// Returning true this layer will bail out from the cmd you give vulkan
	// if returning false, this layer will go all the way to vk core (highly recommend returning false) - program will work exactly the same in debug as it does in final product

	std::ostringstream stream;

	stream << "VKDBG\t";
	if ( flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT )
		stream << "INFO" ;

	if ( flags & VK_DEBUG_REPORT_WARNING_BIT_EXT )
		stream << "WARNING";

	if ( flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT )
		stream << "PERFORMANCE WARNING" ;

	if ( flags & VK_DEBUG_REPORT_ERROR_BIT_EXT )
		stream << "ERROR" ;

	if ( flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT )
		stream << "DEBUG" ;

	stream << "\t@[" << layerPrefix << "]: ";
	stream << msg << std::endl;

	std::cout << stream.str();

 	if ( flags & VK_DEBUG_REPORT_ERROR_BIT_EXT )
		assert(0, stream.str().c_str());

	return false;
}

void VkRenderer::setupDebug()
{
	mDebugCallbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	mDebugCallbackCreateInfo.pfnCallback = VulkanDebugCallback;
	mDebugCallbackCreateInfo.flags =
		VK_DEBUG_REPORT_WARNING_BIT_EXT |
		VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
		VK_DEBUG_REPORT_ERROR_BIT_EXT |
		0;

	mInstanceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
	mInstanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	// device layers not needed here anymore
}

PFN_vkCreateDebugReportCallbackEXT fvkCreateDebugReportCallbackEXT = NULL;
PFN_vkDestroyDebugReportCallbackEXT fvkDestroyDebugReportCallbackEXT = NULL;

void VkRenderer::initDebug()
{
	fvkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(mInstance, "vkCreateDebugReportCallbackEXT");
	fvkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(mInstance, "vkDestroyDebugReportCallbackEXT");

	if ( !fvkCreateDebugReportCallbackEXT || !fvkDestroyDebugReportCallbackEXT )
	{
		assert(0 && "Vulkan ERROR: Can't fetch debug function pointers.");
		std::exit(ARK_ERR);
	}

	fvkCreateDebugReportCallbackEXT(mInstance, &mDebugCallbackCreateInfo, NULL, &mDebugReport);
}

void VkRenderer::deInitDebug()
{
	fvkDestroyDebugReportCallbackEXT(mInstance, mDebugReport, NULL);
	mDebugReport = NULL;
}

void VkRenderer::setupLayersAndExtensions()
{
	// mInstanceExtensions.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);	// for custom embedded systems
	mInstanceExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	mInstanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
	
	mDeviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
}

#else
void VkRenderer::setupDebug() {}

void VkRenderer::initDebug(){}

void VkRenderer::deInitDebug() {}
#endif // BUILD_ENABLE_VULKAN_DEBUG