#pragma once
#include "ArkString.h"

#include <vector>
class JsonUtil
{
public:
	struct PropertyValuePair
	{
		ArkString name;
		ArkString value;
		PropertyValuePair() : name(""), value("") {}
		PropertyValuePair(ArkString n, ArkString v) : name(n), value(v) {}
	};

	static ArkString createJsonFromPropertyValuePairList(std::vector<PropertyValuePair> & list)
	{

		ArkString json = ArkString("{") + ArkString(list.size() > 0 ? "\n" : "");

		for ( unsigned int i = 0 ; i < list.size() ; i++ )
		{
			if ( i ) json += ",\n";
			json += createPropertyStringFromPair(list[i]);
		}


		json += "\n}";

		return json;
	}

	static ArkString createPropertyStringFromPair(PropertyValuePair & const pair) { return pair.name.length() > 0 && pair.value.length() > 0 ? pair.name + ":" + pair.value : ""; }

	static PropertyValuePair getPair(ArkString name, ArkString value)
	{
		PropertyValuePair pair;
		pair.name = name;
		pair.value = value;
		return pair;
	}

	static bool isValidJson(ArkString str)
	{

		int openBracketCount = 0;
		int closeBracketCount = 0;
		bool expectComma = false;
		for ( unsigned int i = 0 ; i < str.length() ; i++ )
		{
			char cc = str.charAt(i);

			switch ( cc )
			{
			case '{':
				openBracketCount++;
				expectComma = false;
				break;
			case '}':
				closeBracketCount++;
				expectComma = openBracketCount > closeBracketCount;
				break;
			case ':': expectComma = true; break;
			case ',': expectComma = false; break;
			}
		}

		return
			openBracketCount > 0
			&& (openBracketCount - closeBracketCount) == 0
			&& !expectComma;
	}

	static std::vector<PropertyValuePair> getPropertyValueListFromJsonString(ArkString jsonString)
	{
		jsonString = jsonString.split('\n').join("");

		if ( !isValidJson(jsonString) ) return std::vector<PropertyValuePair>();


		std::vector<PropertyValuePair> list;

		unsigned int firstCharOfProperty = 0;
		bool gotSemi = false;
		bool gotFirstChar = false;
		for ( unsigned int i = 0 ; i < jsonString.length() ; i++ )
		{
			switch ( jsonString.charAt(i) )
			{
			case '{':
			case '\s':
			case '\t':
				continue;
			case ':':
				gotSemi = true;
				break;
			case '}':
			case ',':
				if ( gotSemi )
				{
					ArkString pv = jsonString.substring(firstCharOfProperty, i);
					firstCharOfProperty = i;
					ArkStringList tempList = pv.split(':');
					list.push_back(PropertyValuePair(tempList.at(0), tempList.at(1)));
					gotFirstChar = false;
				}
				break;
			}

			if ( !gotFirstChar )
			{
				gotFirstChar = true;
				firstCharOfProperty = i;
			}
		}

		return list;
	}
};