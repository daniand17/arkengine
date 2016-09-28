#include <string>
#include <iostream>

#include "ArkEngineCore.h"

int main(int argc, char ** argv)
{
	ArkEngineCore engine;
	try
	{
		engine.run();
	}
	catch ( const std::runtime_error& e )
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	engine.shutdown();
	return EXIT_SUCCESS;
	
	return 0;
}