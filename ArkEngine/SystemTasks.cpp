#include "SystemTasks.h"
#include "ArkDebug.h"
#include "Input.h"

void SystemTask::init()
{

}

void SystemTask::run()
{
	bool done = false;
	do
	{
		if ( Input::GetKeyDown(Input::KeyCodes::Key_W) )
		{

		}
		glfwPollEvents();
	}
	while ( !done );

}
