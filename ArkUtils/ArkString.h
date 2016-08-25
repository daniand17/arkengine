
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
	void operator += (ArkString & const other) { mString += other; }
	void operator = (ArkString & const other) { mString = other; }

	operator std::string() const { return mString; }


	char charAt(unsigned int i) const { return mString.at(i); }


};

std::ostream & operator<<(std::ostream & outStream, ArkString const & arkString)
{
	outStream << (std::string)arkString;
	return outStream;
}