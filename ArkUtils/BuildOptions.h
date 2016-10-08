#pragma once
#define USE_OPENGL 1

#ifndef USE_OPENGL
#define USE_VULKAN 1
#define BUILD_ENABLE_VULKAN_DEBUG			0
#define BUILD_ENABLE_VULKAN_RUNTIME_DEBUG	0


#elif USE_OPENGL

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#endif // !USE_OPENGL


#define COMPILE_TIME_ASSERT(name, n) struct name { char a[(n) ? 1 : -1];}