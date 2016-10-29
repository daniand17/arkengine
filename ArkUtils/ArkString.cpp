#include "ArkString.h"

bool operator == (ArkString const & lhs, ArkString const & rhs)
{
	size_t len = lhs.length();

	if ( len != rhs.length() )
		return false;

	for ( unsigned int i = 0 ; i < len ; i++ )
		if ( lhs.charAt(i) != rhs.charAt(i) )
			return false;

	return true;
}


bool operator!=(ArkString const & lhs, ArkString const & rhs)
{
	return !(lhs == rhs);
}


ArkString operator+(ArkString const & lhs, ArkString const & rhs)
{
	ArkString l(lhs);
	l += rhs;
	return l;
}

bool operator<(ArkString const & lhs, ArkString const & rhs)
{
	return lhs.toStdString() < rhs.toStdString();
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


ArkStringList ArkString::split(char delim) const
{
	ArkStringList list;
	if ( mString.length() == 0 )
		return list;

	size_t i = 0;
	size_t pos = mString.find(delim);

	size_t siz = mString.length();
	while ( pos < siz )
	{
		list.push_back(ArkString(mString.substr(i, pos - i)));
		i = ++pos;
		pos = mString.find(delim, pos);

		if ( pos >= siz )
			list.push_back(mString.substr(i, siz));
	}

	if ( list.size() == 0 )
		list.push_back(mString);
	return list;
}


ArkString ArkStringList::join(ArkString delim) const
{
	ArkString joinedString;
	size_t siz = m_stringList.size();
	for ( unsigned i = 0 ; i < siz; i++ )
	{
		joinedString += m_stringList[i];
		if ( i + 1 != siz )
			joinedString += delim;
	}
	return joinedString;
}


ArkString ArkStringList::pop_back()
{
	ArkString retVal = m_stringList[m_stringList.size() - 1];
	m_stringList.pop_back();
	return retVal;
}