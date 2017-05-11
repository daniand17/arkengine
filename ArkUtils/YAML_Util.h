#pragma once

#include "ArkString.h"

#define IN_BUF_SIZ 80
class YAML_Generator
{
public:
	static ArkString genObjectHeader(unsigned classId, unsigned fileId)
	{
		return "--- !u!" + ArkString::Number(classId) + " &" + ArkString::Number(fileId) + "\n";
	}

	static ArkString genObjectNameHeader(ArkString objectName)
	{
		return objectName + ":";
	}

	static ArkString genStringProperty(ArkString propertyName, ArkString propertyValue)
	{
		return __genPropertyNameString(propertyName) + propertyValue;
	}

	static ArkString genBoolProperty(ArkString propertyName, bool propertyValue)
	{
		return __genPropertyNameString(propertyName) + ArkString::Number(propertyValue ? 1 : 0);
	}

	static ArkString genRawProperty(ArkString propertyName, ArkString propertyValue)
	{
		return __genPropertyNameString(propertyName) + propertyValue;
	}

	static ArkString genNumberProperty(ArkString propertyName, unsigned number)
	{
		return __genPropertyNameString(propertyName) + ArkString::Number(number);
	}

	static ArkString genNumberProperty(ArkString propertyName, float number)
	{
		return __genPropertyNameString(propertyName) + ArkString::Number(number);
	}

private:
	static ArkString __genPropertyNameString(ArkString propertyName)
	{
		return "\n\t" + propertyName + ":\t";
	}
};



class YAML_Extractor
{
public:
	static bool extractObjectHeader(ArkString line, unsigned & classId, unsigned & uniqueId)
	{
		bool success = sscanf_s(line.c_str(), "\n--- !u!%d &%d", &classId, &uniqueId) == 2;
		return success;
	}

	static bool extractObjectNameHeader(ArkString line, ArkString & result)
	{
		char res[IN_BUF_SIZ];
		bool success = sscanf_s(line.c_str(), "%s:", res, IN_BUF_SIZ) == 1;
		result = res;
		return success && result.length() > 0;
	}

	static bool extractStringProperty(ArkString line, ArkString propertyName, ArkString & result)
	{
		char res[IN_BUF_SIZ];

		bool success = sscanf_s(line.c_str(), __genFormatString(propertyName, "%s").c_str(), res, IN_BUF_SIZ) == 1;

		result = ArkString(res);

		return success;
	}

	static bool extractBoolProperty(ArkString line, ArkString propertyName, bool & result)
	{
		int res(0);
		bool success = sscanf_s(line.c_str(), __genFormatString(propertyName, "%d").c_str(), &res) == 1;
		result = res == 1;
		return success;

	}

	static bool extractRawProperty(ArkString line, ArkString propertyName, ArkString & result)
	{
		char raw[IN_BUF_SIZ];
		bool success = sscanf_s(line.c_str(), __genFormatString(propertyName, "%s").c_str(), raw, IN_BUF_SIZ) == 1;
		result = raw;
		return success;
	}

	static bool extractNumberProperty(ArkString line, ArkString propertyName, unsigned & number)
	{
		return sscanf_s(line.c_str(), __genFormatString(propertyName, "%d").c_str(), &number) == 1;
	}

	static bool extractNumberProperty(ArkString line, ArkString propertyName, float & number)
	{
		return sscanf_s(line.c_str(), __genFormatString(propertyName, "%f").c_str(), &number) == 1;
	}

	static bool containsProperty(ArkString line, ArkString propertyName)
	{
		return line.contains(propertyName);
	}

private:

	static ArkString __genFormatString(ArkString propertyName, ArkString formatSpecifiers)
	{
		return "\t" + propertyName + ":\t" + formatSpecifiers;
	}
};