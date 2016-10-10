#include "BuildOptions.h"
#include "ArkEngineCore.h"

class Input
{
public:
	enum KeyCodes
	{
		KEY_INVALID = -1, // Needs to be the first

		Key_A = 0,
		Key_B,
		Key_C,
		Key_D,
		Key_E,
		Key_F,
		Key_G,
		Key_H,
		Key_I,
		Key_J,
		Key_K,
		Key_L,
		Key_M,
		Key_N,
		Key_O,
		Key_P,
		Key_Q,
		Key_R,
		Key_S,
		Key_T,
		Key_U,
		Key_V,
		Key_W,
		Key_X,
		Key_Y,
		Key_Z,

		NUM_KEYS			// Needs to be the last
	};
	
	static bool GetKeyDown(KeyCodes keyCode);
	
private:
	static bool keys[NUM_KEYS];
	static KeyCodes GetArkEngineKeyMapping(unsigned int glfwKey);
	static unsigned int GetGlfwKeyMapping(Input::KeyCodes key);
};