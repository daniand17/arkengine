#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include "ArkString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test_ArkUtils
{
	TEST_CLASS(ArkString_Test)
	{
	public:

		TEST_METHOD(Constructor)
		{
			ArkString str = "Hello";
			Assert::AreEqual(str.toStdString(), std::string("Hello"));
		}

		TEST_METHOD(Equality)
		{
			Assert::IsTrue(ArkString("Hello") == ArkString("Hello"));
			Assert::IsTrue(ArkString("Hello") != ArkString("sup"));
		}

		TEST_METHOD(OStream)
		{
			std::cout << ArkString("hello") << std::endl;
			puts(ArkString("hello").c_str());
		}

		TEST_METHOD(Concatenate)
		{

			ArkString hello = "Hello";
			hello += " world";

			Assert::AreEqual(hello.c_str(), ArkString("Hello world").c_str());
			Assert::AreEqual(hello.toStdString(), ArkString("Hello world").toStdString());
		}

	};
}