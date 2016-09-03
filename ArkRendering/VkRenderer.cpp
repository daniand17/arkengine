#include <cstdlib>
#include <assert.h>
#include <vector>
#include <iostream>
#include <sstream>

#include <Windows.h>

#include "VkRenderer.h"
#include "Shared.h"

VkRenderer::VkRenderer()
{
	_setupDebug();
	_initInstance();
	_initDebug();
	_initDevice();
}

VkRenderer::~VkRenderer()
{
	_deInitDevice();
	_deInitDebug();
	_deInitInstance();
}

void VkRenderer::_initInstance()
{
	VkApplicationInfo applicationInfo {};
	applicationInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.apiVersion			= VK_MAKE_VERSION(1, 0, 24);	// NOTE Set vk version here
	applicationInfo.applicationVersion	= VK_MAKE_VERSION(0, 1, 0);
	applicationInfo.pApplicationName	= "Ark Engine 0.1.0";

	VkInstanceCreateInfo instanceCreateInfo {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &applicationInfo;
	instanceCreateInfo.enabledLayerCount = mInstanceLayers.size();
	instanceCreateInfo.ppEnabledLayerNames = mInstanceLayers.data();
	instanceCreateInfo.enabledExtensionCount = mInstanceExtensions.size();
	instanceCreateInfo.ppEnabledExtensionNames = mInstanceExtensions.data();
	instanceCreateInfo.pNext = &mDebugCallbackCreateInfo;

	ErrorCheck(vkCreateInstance(&instanceCreateInfo, NULL /* TODO Memory alloc stuff */, &mInstance));
}

void VkRenderer::_deInitInstance()
{
	vkDestroyInstance(mInstance, NULL /* TODO Memory management for VkRenderer::_DeInit*/);
	mInstance = NULL;
}

void VkRenderer::_initDevice()
{
	_getPhysicalDeviceAndProperties();

	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, NULL);
		std::vector<VkLayerProperties> layerPropertyList(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, layerPropertyList.data());
	}

	{
		uint32_t layerCount;
		vkEnumerateDeviceLayerProperties(mGpu, &layerCount, NULL);
		std::vector<VkLayerProperties> layerPropertyList(layerCount);
		vkEnumerateDeviceLayerProperties(mGpu, &layerCount, layerPropertyList.data());
	}

	float queuePriorities[]{1.0f};
	VkDeviceQueueCreateInfo deviceQueueCreateInfo{};
	deviceQueueCreateInfo.sType				= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.queueFamilyIndex	= getFamilyIndex();	// which type of queue family we are going to use (can ask the GPU)
	deviceQueueCreateInfo.queueCount		= 1;
	deviceQueueCreateInfo.pQueuePriorities	= queuePriorities;	// Tell vk driver which queue takes priority (how much compute time per queue)

	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType					= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount	= 1;
	deviceCreateInfo.pQueueCreateInfos		= &deviceQueueCreateInfo;
	deviceCreateInfo.enabledLayerCount		= mDeviceExtensions.size();
	deviceCreateInfo.ppEnabledLayerNames	= mDeviceExtensions.data();

	ErrorCheck(vkCreateDevice(mGpu, &deviceCreateInfo, nullptr /*TODO memory allocator*/, &mDevice));
}


int VkRenderer::getFamilyIndex()
{
	uint32_t familyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(mGpu, &familyCount, NULL);
	std::vector<VkQueueFamilyProperties> familyPropertyList(familyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(mGpu, &familyCount, familyPropertyList.data());

	bool found = false;
	for ( uint32_t i = 0; i < familyCount ; i++ )
		if ( familyPropertyList[i].queueFlags & VK_QUEUE_GRAPHICS_BIT )
			return i;

	if ( !found )
	{
		assert(0 && "Vulkan ERROR: Queue family supporting graphics not found.");
		std::exit(-1);	// TODO maybe do something else with exiting?
	}

	return -1;
}

void VkRenderer::_getPhysicalDeviceAndProperties()
{
	uint32_t gpuCount = 0;
	vkEnumeratePhysicalDevices(mInstance, &gpuCount, NULL);
	std::vector<VkPhysicalDevice> gpuList(gpuCount);
	vkEnumeratePhysicalDevices(mInstance, &gpuCount, gpuList.data());	// on second pass, populates the list of all the handles of all the gpus
	mGpu = gpuList[0];	// TODO assumes the first in the list is the best one, improve selection
	vkGetPhysicalDeviceProperties(mGpu, &mGpuProperties);
}

void VkRenderer::_deInitDevice()
{
	vkDestroyDevice(mDevice, NULL /* TODO memory management */);
	mDevice = NULL;
}

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

void VkRenderer::_setupDebug()
{
	mDebugCallbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	mDebugCallbackCreateInfo.pfnCallback = VulkanDebugCallback;
	mDebugCallbackCreateInfo.flags =
		//VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
		VK_DEBUG_REPORT_WARNING_BIT_EXT	| 
		VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
		VK_DEBUG_REPORT_ERROR_BIT_EXT |
		//VK_DEBUG_REPORT_DEBUG_BIT_EXT |
		0;

	mInstanceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
	//mInstanceLayers.push_back("VK_LAYER_GOOGLE_threading");
	////mInstanceLayers.push_back("VK_LAYER_LUNARG_draw_state");
	//mInstanceLayers.push_back("VK_LAYER_LUNARG_image");
	////mInstanceLayers.push_back("VK_LAYER_LUNARG_mem_tracker");
	//mInstanceLayers.push_back("VK_LAYER_LUNARG_object_tracker");
	//mInstanceLayers.push_back("VK_LAYER_LUNARG_parameter_validation");

	mInstanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	// device layers not needed here anymore
}

PFN_vkCreateDebugReportCallbackEXT fvkCreateDebugReportCallbackEXT		= NULL;
PFN_vkDestroyDebugReportCallbackEXT fvkDestroyDebugReportCallbackEXT	= NULL;

void VkRenderer::_initDebug()
{
	fvkCreateDebugReportCallbackEXT		= (PFN_vkCreateDebugReportCallbackEXT)	vkGetInstanceProcAddr(mInstance, "vkCreateDebugReportCallbackEXT");
	fvkDestroyDebugReportCallbackEXT	= (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(mInstance, "vkDestroyDebugReportCallbackEXT");

	if ( !fvkCreateDebugReportCallbackEXT || !fvkDestroyDebugReportCallbackEXT )
	{
		assert(0 && "Vulkan ERROR: Can't fetch debug function pointers.");
		std::exit(-1);
	}

	fvkCreateDebugReportCallbackEXT(mInstance, &mDebugCallbackCreateInfo, NULL, &mDebugReport);
}

void VkRenderer::_deInitDebug()
{
	fvkDestroyDebugReportCallbackEXT(mInstance, mDebugReport, NULL);
	mDebugReport = NULL;
}
