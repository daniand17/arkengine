
#include <string>
#include <ostream>
#include <istream>

class ArkString
{
private:
	std::string mString;

public:

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
};
std::ostream & operator<<(std::ostream & outStream, ArkString const & theString);
bool operator == (ArkString const & lhs, ArkString const & rhs);
bool operator != (ArkString const & lhs, ArkString const & rhs);

