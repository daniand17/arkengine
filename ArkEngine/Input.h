#include "BuildOptions.h"
#include "ArkEngineCore.h"

namespace Input
{
	enum KeyCodes
	{
		KEY_INVALID = -1, // Needs to be the first

		KEY_W = 0,
		KEY_S,
		KEY_A,
		KEY_D,

		NUM_KEYS			// Needs to be the last
	};
	
	bool GetKeyDown(KeyCodes keyCode)
	{
		ArkEngineCore * inst = ArkEngineCore::Instance();
		ArkWindow const * win;
		if ( inst )
			win = inst->GetMainWindowHandle();

		if ( win )
			return glfwGetKey(win->getOSWindowHandle(), GetGlfwKeyMapping(keyCode) == GLFW_PRESS);
		else
			return false;
	}

	KeyCodes GetArkEngineKeyMapping(unsigned int glfwKey)
	{
		switch ( glfwKey )
		{
		case GLFW_KEY_W: return KEY_W;
		case GLFW_KEY_S: return KEY_S;
		case GLFW_KEY_A: return KEY_A;
		case GLFW_KEY_D: return KEY_D;
		}
	}

	unsigned int GetGlfwKeyMapping(KeyCodes key)
	{
		switch ( key )
		{
		case KEY_W: return GLFW_KEY_W;
		case KEY_S: return GLFW_KEY_S;
		case KEY_A: return GLFW_KEY_A;
		case KEY_D: return GLFW_KEY_D;
		}
	}
}