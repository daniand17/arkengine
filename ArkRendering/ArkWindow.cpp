#include <assert.h>
#include <vector>

#include "ArkWindow.h"
#include "VkRenderer.h"
#include "Shared.h"

uint64_t ArkWindow::_win32_class_id_counter = 0;

ArkWindow::ArkWindow(VkRenderer * renderer, uint32_t sizeX, uint32_t sizeY, ArkString name) 
	: mWindowShouldRun(true)
	, mRenderer(renderer)
	, mSwapchainManager(renderer)
	, mSurface(NULL)
	, mSizeX(sizeX)
	, mSizeY(sizeY)
	, mWindowName(name)
{
	initOSWindow();
	initSurface();
	// init swapchain manager here
	mSwapchainManager.init(mSurface);

}

ArkWindow::~ArkWindow()
{
	
}

void ArkWindow::Close()
{
	mWindowShouldRun = false;
	
	// deinit swapchain manager here
	deInitSurface();
	deInitOSWindow();
}

bool ArkWindow::Update()
{
	updateOSWindow();
	return mWindowShouldRun;
}

void ArkWindow::initSurface()
{
	initOSSurface();

	VkPhysicalDevice const & gpu = mRenderer->GetVkPhysicalDevice();
	
	VkBool32 supported = false;
	vkGetPhysicalDeviceSurfaceSupportKHR(gpu, mRenderer->GetQueueFamilyIndex(), mSurface, &supported);

	if ( !supported )
	{
		assert(0 && "WSI not supported");
		std::exit(-1);
	}

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gpu, mSurface, &mSurfaceCapabilities);

	if ( mSurfaceCapabilities.currentExtent.width < UINT32_MAX )	// Don't need to check height because eithe ris good
	{
		mSizeX = mSurfaceCapabilities.currentExtent.width;
		mSizeY = mSurfaceCapabilities.currentExtent.height;
	}

	{
		uint32_t formatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, mSurface, &formatCount, NULL);
		if ( formatCount == 0 )
		{
			assert(0 && "Surface formats missing.");
			std::exit(-1);
		}
		std::vector<VkSurfaceFormatKHR> formats(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, mSurface, &formatCount, formats.data()); // tells us the format our eventual framebuffers should have. Those image formats should match these surface formats
		if ( formats[0].format == VK_FORMAT_UNDEFINED )
		{
			mSurfaceFormat.format = VK_FORMAT_B8G8R8A8_UNORM;
			mSurfaceFormat.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		}
		else
			mSurfaceFormat = formats[0];
	}
}

void ArkWindow::deInitSurface()
{
	// TODO this isn't destroying
	vkDestroySurfaceKHR(mRenderer->GetVkInstance(), mSurface, NULL /* TODO alloc callback */);
	mSurface = NULL;
}