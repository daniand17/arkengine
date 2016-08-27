#include "ArkString.h"

bool operator == (ArkString const & lhs, ArkString const & rhs)
{
	size_t len = lhs.length();

	if ( len != rhs.length() )
		return false;

	for ( size_t i = 0 ; i < len ; i++ )
		if ( lhs.charAt(i) != rhs.charAt(i) )
			return false;

	return true;
}

bool operator!=(ArkString const & lhs, ArkString const & rhs)
{
	return !(lhs == rhs);
}

std::ostream & operator<<(std::ostream & outStream, ArkString const & theString)
{
	outStream << (std::string) theString;
	return outStream;
}

char const * ArkString::c_str() const
{
	return 	mString.c_str();
}
