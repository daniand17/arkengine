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

		TEST_METHOD(Concatenate_Binary)
		{
			ArkString hello = "Hello";
			hello = hello + " world!";

			Assert::AreEqual(hello.toStdString(), ArkString("Hello world!").toStdString());
		}

		TEST_METHOD(Split)
		{
			ArkString hello = "Hello world!";
			ArkStringList strList = hello.split(' ');
			// TODO THis is not enough coverage
			Assert::AreEqual(static_cast<size_t>(2), strList.size());
			Assert::AreEqual(ArkString("Hello").toStdString(), strList.at(0).toStdString());
			Assert::AreEqual(ArkString("world!").toStdString(), strList.at(1).toStdString());

			ArkString longerString = "Hello world and some other things! Things! Things!";
			ArkStringList longerStrList = longerString.split(' ');
			Assert::AreEqual(static_cast<size_t>(8), longerStrList.size());
			Assert::AreEqual(std::string("Hello"), longerStrList.at(0).toStdString());
			Assert::AreEqual(std::string("world"), longerStrList.at(1).toStdString());
			Assert::AreEqual(std::string("and"), longerStrList.at(2).toStdString());
			Assert::AreEqual(std::string("some"), longerStrList.at(3).toStdString());
			Assert::AreEqual(std::string("other"), longerStrList.at(4).toStdString());
			Assert::AreEqual(std::string("things!"), longerStrList.at(5).toStdString());
			Assert::AreEqual(std::string("Things!"), longerStrList.at(6).toStdString());
			Assert::AreEqual(std::string("Things!"), longerStrList.at(7).toStdString());
		}

		TEST_METHOD(Split_And_Join)
		{
			ArkString hello = "Hello this world is fantastic! world!";
			ArkStringList split = hello.split(' ');
			ArkString result = split.join(" ");

			Assert::AreEqual(static_cast<size_t>(6), split.size());
			Assert::AreEqual(hello.toStdString(), result.toStdString());
		}

		TEST_METHOD(Nothing_To_Split_Returns_String)
		{
			ArkString hello = "hello world!";
			ArkStringList list = hello.split(',');
			Assert::AreEqual(ArkString("hello world!").toStdString(), list.at(0).toStdString());
		}

	};
}