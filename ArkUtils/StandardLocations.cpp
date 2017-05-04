#include "StandardLocations.h"

#include <ShlObj.h>

ArkString StandardLocations::writeableLocation(Location location)
{
	TCHAR szPath[MAX_PATH];

	if ( SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath)) )
	{
		return ArkString(szPath);
	}

	return ArkString("");
}
