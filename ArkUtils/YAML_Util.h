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
		return __genPropertyNameString(propertyName) + propertyValue + "\"";
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
	static bool extractObjectHeader(ArkString line, unsigned & classId, unsigned uniqueId)
	{
		bool success = sscanf_s(line.c_str(), "--- !u!%d &%d", &classId, &uniqueId) == 2;
		return success;
	}

	static bool extractObjectNameHeader(ArkString line, ArkString & result)
	{
		char res[IN_BUF_SIZ];
		bool success = sscanf_s(line.c_str(), "%s:", res, IN_BUF_SIZ) == 1;
		result = res;
		return success && result.length() > 0;
	}
	
	static bool extractStringProperty(ArkString line, ArkString & result)
	{
		char res[IN_BUF_SIZ];

		bool success = sscanf_s(line.c_str(), ":\t\"%s\"", res, IN_BUF_SIZ) == 1;

		result = ArkString(res);

		return success;
	}

	static bool extractBoolProperty(ArkString line, bool & result)
	{
		int res(0);
		bool success = sscanf_s(line.c_str(), ":\t%d", &res) == 1;
		result = res == 1;
		return success;

	}

	static bool extractRawProperty(ArkString line, ArkString & result)
	{
		char raw[IN_BUF_SIZ];
		bool success = sscanf_s(line.c_str(), ":\t%s", raw, IN_BUF_SIZ) == 1;
		result = raw;
		return success;
	}

	static bool extractNumberProperty(ArkString line, unsigned & number)
	{
		return sscanf_s(line.c_str(), ":\t%d", &number) == 1;
	}

	static bool extractNumberProperty(ArkString line, float & number)
	{
		return sscanf_s(line.c_str(), ":\t%f", &number) == 1;
	}

	static bool isProperty(ArkString line, ArkString propertyName)
	{
		return line.contains(propertyName);
	}
};