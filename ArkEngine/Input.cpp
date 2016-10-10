#include "Input.h"
#include "ArkWindow.h"

bool Input::keys[NUM_KEYS];

bool Input::GetKeyDown(KeyCodes keyCode)
{
	ArkEngineCore * inst = ArkEngineCore::Instance();
	if ( inst )
	{
		ArkWindow const * win = inst->GetMainWindowHandle();

		if ( win )
			return glfwGetKey(win->getOSWindowHandle(), GetGlfwKeyMapping(keyCode)) == GLFW_PRESS;
	}

	return false;
}

Input::KeyCodes Input::GetArkEngineKeyMapping(unsigned int glfwKey)
{
	switch ( glfwKey )
	{
	case GLFW_KEY_W: return Key_W;
	case GLFW_KEY_S: return Key_S;
	case GLFW_KEY_A: return Key_A;
	case GLFW_KEY_D: return Key_D;
	default:
		return KEY_INVALID;
	}

}

unsigned int Input::GetGlfwKeyMapping(Input::KeyCodes key)
{
	switch ( key )
	{
	case Key_W: return GLFW_KEY_W;
	case Key_S: return GLFW_KEY_S;
	case Key_A: return GLFW_KEY_A;
	case Key_D: return GLFW_KEY_D;
	}
	return -1;
}