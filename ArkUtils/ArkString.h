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
	size_t length() const { return mString.length(); }

	operator std::string() const { return mString; }
	char charAt(unsigned int i) const { return mString.at(i); }
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
	size_t size() const { return mStringList.size(); }
	ArkString join(ArkString delim) const;
	ArkString at(unsigned index) { return index < mStringList.size() ? mStringList[index] : ArkString(); }
	void push_back(ArkString str) { mStringList.push_back(str); }
	ArkString pop_back();
private:
	std::vector<ArkString> mStringList;
};
