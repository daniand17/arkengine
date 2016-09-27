#pragma once

#if defined(_WIN32)

#define VK_USE_PLATFORM_WIN32_KHR 1// Used to get extra functions in vulkan
#define PLATFORM_SURFACE_EXTENSION_NAME VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#include <Windows.h>

#elif defined( __linux)

#define VK_USE_PLATFORM_XCB_KHR 1
#define PLATFORM_SURFACE_EXTENSION_NAME VK_KHR_XCB_SURFACE_EXTENSION_NAME
#include <xcb/xcb.h>

#else
#error Platform not yet supported
#endif //define _WIN32

#include <vulkan.h>
