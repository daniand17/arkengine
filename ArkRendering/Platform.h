#pragma once

#ifdef _WIN32

#define VK_USE_PLATFORM_WIN32_KHR 1// Used to get extra functions in vulkan
#include <Windows.h>
#else
#error Platform not yet supported
#endif //define _WIN32

#include <vulkan.h>
