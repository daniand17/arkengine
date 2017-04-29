#pragma once
#include <string>
#include <ostream>
#include <istream>
#include <vector>

class ArkStringList;

class ArkString
{
private:
	std::string m_string;

public:
	ArkString() : m_string("") {}
	ArkString(std::string str) : m_string(str) {}
	ArkString(char * c) : m_string(c) {}

	// Operators
	void operator += (ArkString const & other) { m_string += other; }
	void operator = (ArkString const & other) { m_string = other; }
	bool operator < (ArkString const & other) const { return m_string < other.m_string; }
	size_t length() const { return m_string.length(); }

	operator std::string() const { return m_string; }
	char charAt(size_t i) const { return m_string.at(i); }
	std::string toStdString() const { return m_string; }
	char const * c_str() const;

	ArkStringList split(char delim) const;

	ArkString substring(unsigned int start, unsigned int end) const { return m_string.substr(start, end - start); }

	static ArkString Number(unsigned number) { return ArkString(std::to_string(number)); }
	static ArkString Number(int number) { return ArkString(std::to_string(number)); }
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
