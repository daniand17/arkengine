#include <string>
#include <iostream>

#include "ArkEngineCore.h"

int main(int argc, char ** argv)
{
	ArkEngineCore::InitEngine();
	try
	{
		ArkEngineCore::Instance()->run();
	}
	catch ( const std::runtime_error& e )
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	ArkEngineCore::Instance()->shutdown();
	return EXIT_SUCCESS;
	
	return 0;
}