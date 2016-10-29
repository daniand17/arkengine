#pragma once
#include <string>
#include <ostream>
#include <istream>
#include <vector>

class ArkStringList;

class ArkString
{
private:
	std::string mString;

public:
	ArkString() : mString("") {}
	ArkString(std::string str) : mString(str) {}
	ArkString(char * c) : mString(c) {}

	// Operators
	void operator += (ArkString const & other) { mString += other; }
	void operator = (ArkString const & other) { mString = other; }
	bool operator < (ArkString const & other) const { return strcmp(mString.c_str(), other.mString.c_str()) < 0; }
	size_t length() const { return mString.length(); }

	operator std::string() const { return mString; }
	char charAt(size_t i) const { return mString.at(i); }
	std::string toStdString() const { return mString; }
	char const * c_str() const;

	ArkStringList split(char delim) const;

	static ArkString Number(unsigned number) { return ArkString(std::to_string(number)); }
	static ArkString Number(int number) { return ArkString(std::to_string(number)); }
	static ArkString Number(size_t number) { return ArkString(std::to_string(number)); }
	static ArkString Number(double number) { return ArkString(std::to_string(number)); }
	static ArkString Number(float number) { return ArkString(std::to_string(number)); }
};

std::ostream & operator<<(std::ostream & outStream, ArkString const & theString);
bool operator == (ArkString const & lhs, ArkString const & rhs);
bool operator != (ArkString const & lhs, ArkString const & rhs);
ArkString operator + (ArkString const & lhs, ArkString const & rhs);

class ArkStringList
{
public:
	size_t size() const { return m_stringList.size(); }
	ArkString join(ArkString delim) const;
	ArkString at(size_t index) { return index < m_stringList.size() ? m_stringList[index] : ArkString(); }
	ArkString getLast() const { return m_stringList.back(); }
	ArkString getFirst() const { return m_stringList.front(); }
	void push_back(ArkString str) { m_stringList.push_back(str); }
	ArkString pop_back();
private:
	std::vector<ArkString> m_stringList;
};
