#include <Windows.h>

#include "SystemDirectory.h"

bool SystemDirectory::createDirectory(ArkString directoryName)
{
	bool created = false;
	if ( CreateDirectory(directoryName.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError() )
	{
		//Debug::Log("created directory " + directoryName);
		created = true;
		// do directory creation stuff
	}
	else
	{
		//Debug::Err("failed to create directory " + directoryName);
		created = false;
		// failed to create directory
	}

	return created;
}

bool SystemDirectory::directoryExists(ArkString directory)
{
	return (GetFileAttributes(directory.c_str()) & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY;
}
