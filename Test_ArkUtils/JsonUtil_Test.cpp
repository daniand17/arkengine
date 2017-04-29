#include "stdafx.h"
#include "CppUnitTest.h"

#include "JsonUtil.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define SIZE_T(exp) static_cast<unsigned int>(exp)
namespace Test_ArkUtils
{
	TEST_CLASS(JsonUtil_Test)
	{
		TEST_METHOD(JsonUtil_PropertyString)
		{
			JsonUtil::PropertyValuePair pair;

			pair.name = "property";
			pair.value = "value";
			ArkString result = JsonUtil::createPropertyStringFromPair(pair);

			Assert::AreEqual(ArkString("property:value").toStdString(), result.toStdString());
		}


		TEST_METHOD(JsonUtil_CreateEmptyString)
		{
			ArkString res = JsonUtil::createPropertyStringFromPair(JsonUtil::getPair("", ""));
			Assert::AreEqual(ArkString("").toStdString(), res.toStdString());
		}


		TEST_METHOD(JsonUtil_JsonFromEmptyList)
		{
			std::vector <JsonUtil::PropertyValuePair> pairs;

			ArkString result = JsonUtil::createJsonFromPropertyValuePairList(pairs);
			Assert::AreEqual(ArkString("{\n}").toStdString(), result.toStdString());
		}


		TEST_METHOD(JsonUtil_JsonFromListOf)
		{
			std::vector<JsonUtil::PropertyValuePair> pairs;
			pairs.push_back(JsonUtil::getPair("andy", "pandy"));
			pairs.push_back(JsonUtil::getPair("cotton", "candy"));

			ArkString result = "{\n";
			result += "andy:pandy,\n";
			result += "cotton:candy";
			result += "\n}";

			Assert::AreEqual(result.toStdString(), JsonUtil::createJsonFromPropertyValuePairList(pairs).toStdString());
		}

		
		TEST_METHOD(JsonUtil_SimpleNestedJson)
		{
			std::vector<JsonUtil::PropertyValuePair> pairs0;
			pairs0.push_back(JsonUtil::getPair("andy", "pandy"));
			pairs0.push_back(JsonUtil::getPair("cotton", "candy"));

			std::vector<JsonUtil::PropertyValuePair> nestedPairs;

			nestedPairs.push_back(JsonUtil::getPair("andy", "pandy"));
			nestedPairs.push_back(JsonUtil::getPair("cotton", "candy"));
			
			pairs0.push_back(JsonUtil::getPair("nested", JsonUtil::createJsonFromPropertyValuePairList(nestedPairs)));

			ArkString result = "{\n";
			result += "andy:pandy,\n";
			result += "cotton:candy,\n";
			result += "nested:{\n";
			result += "andy:pandy,\n";
			result += "cotton:candy";
			result += "\n}";
			result += "\n}";

			Assert::AreEqual(result.toStdString(), JsonUtil::createJsonFromPropertyValuePairList(pairs0).toStdString());
		}

		TEST_METHOD(JsonUtil_IsJson)
		{
			std::vector<JsonUtil::PropertyValuePair> pairs;

			pairs.push_back(JsonUtil::getPair("andy", "pandy"));
			pairs.push_back(JsonUtil::getPair("candy", "dandy"));

			ArkString result = JsonUtil::createJsonFromPropertyValuePairList(pairs);

			Assert::IsTrue(JsonUtil::isValidJson(result));

			Assert::IsFalse(JsonUtil::isValidJson("andyPandy:cottonCandy"));


			ArkString res = JsonUtil::createJsonFromPropertyValuePairList(std::vector<JsonUtil::PropertyValuePair>());
			Assert::IsTrue(JsonUtil::isValidJson(res));
		}

		TEST_METHOD(JsonUtil_NestedJsonIsValid)
		{
			std::vector<JsonUtil::PropertyValuePair> pairs;
			pairs.push_back(JsonUtil::getPair("andy", "pandy"));

			std::vector<JsonUtil::PropertyValuePair> pairs1;
			pairs1.push_back(JsonUtil::getPair("pandy", "candy"));

			pairs.push_back(JsonUtil::getPair("nested", JsonUtil::createJsonFromPropertyValuePairList(pairs1)));
			ArkString result = JsonUtil::createJsonFromPropertyValuePairList(pairs);

			JsonUtil::isValidJson(result);
		}

		TEST_METHOD(JsonUtil_SimpleGetPropertyValue)
		{
			std::vector<JsonUtil::PropertyValuePair> pairs;
			pairs.push_back(JsonUtil::getPair("andy", "pandy"));

			ArkString json = JsonUtil::createJsonFromPropertyValuePairList(pairs);

			std::vector<JsonUtil::PropertyValuePair> list = JsonUtil::getPropertyValueListFromJsonString(json);

			Assert::AreEqual(SIZE_T(1), list.size());

			Assert::AreEqual(ArkString("andy").toStdString(), list.at(0).name.toStdString());
			Assert::AreEqual(ArkString("pandy").toStdString(), list.at(0).value.toStdString());
		}


		TEST_METHOD(JsonUtil_GetPropertyValuesFrom2LineJson)
		{
			std::vector<JsonUtil::PropertyValuePair> pairs;
			pairs.push_back(JsonUtil::getPair("a", "b"));
			pairs.push_back(JsonUtil::getPair("andy", "pandy"));

			std::vector<JsonUtil::PropertyValuePair> result = JsonUtil::getPropertyValueListFromJsonString(JsonUtil::createJsonFromPropertyValuePairList(pairs));

			Assert::AreEqual(pairs.size(), result.size());

			for ( unsigned int i = 0 ; i < result.size() ; i++ )
			{
				Assert::AreEqual(pairs.at(i).name.toStdString(), result.at(i).name.toStdString());
				Assert::AreEqual(pairs.at(i).value.toStdString(), result.at(i).value.toStdString());
			}


		}
	};
}