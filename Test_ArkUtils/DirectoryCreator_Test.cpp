#include "stdafx.h"
#include "CppUnitTest.h"

#include <exception>

#include "SystemDirectory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test_ArkUtils
{
	TEST_CLASS(Directory_Creation)
	{
	public:
		TEST_METHOD(Nonexistent_Directory_Does_Not_Exist)
		{
			Assert::IsFalse(!SystemDirectory::directoryExists("Helloworld"));
		}

		TEST_METHOD(Create)
		{
			SystemDirectory::createDirectory("HelloTestFolder");
			Assert::IsTrue(SystemDirectory::directoryExists("HelloTestFolder"));
		}
	};
}