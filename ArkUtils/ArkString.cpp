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
	return 	m_string.c_str();
}



size_t ArkString::indexOf(ArkString const & other) const
{
	char const * lhs = m_string.c_str();
	char const * rhs = other.c_str();

	size_t thisLen(m_string.length()), otherLen(other.length());

	for ( size_t i = 0 ; i < thisLen ; i++ )
	{
		bool valid = true;
		for ( size_t k = 0 ; k < otherLen ; k++ )
		{
			size_t compIndex(i + k);

			if ( compIndex < thisLen && lhs[compIndex] != rhs[k] )
			{
				valid = false;
				break;
			}
		}

		if ( valid )
		{
			return i;
		}
	}

	return -1;
}



ArkStringList ArkString::split(char delim) const
{
	ArkStringList list;
	if ( m_string.length() == 0 )
		return list;

	size_t i = 0;
	size_t pos = m_string.find(delim);

	size_t siz = m_string.length();
	while ( pos < siz )
	{
		list.push_back(ArkString(m_string.substr(i, pos - i)));
		i = ++pos;
		pos = m_string.find(delim, pos);

		if ( pos >= siz )
			list.push_back(m_string.substr(i, siz));
	}

	if ( list.size() == 0 )
		list.push_back(m_string);
	return list;
}



ArkStringList ArkString::split(ArkString delim) const
{
	ArkStringList strList;

	if ( m_string.length() == 0 )
	{
		return strList;
	}

	return ArkStringList();
}



ArkString ArkStringList::join(ArkString delim) const
{
	ArkString joinedString;
	for ( std::list<ArkString>::const_iterator it(m_stringList.begin()); it != m_stringList.end() ; it++ )
	{
		joinedString += *it;
		if ( (++it) != m_stringList.end() )
		{
			joinedString += delim;
		}
		it--;
	}
	return joinedString;
}



ArkString ArkStringList::pop_back()
{
	ArkString retVal = *(std::next(m_stringList.begin(), m_stringList.size() - 1));
	m_stringList.pop_back();
	return retVal;
}