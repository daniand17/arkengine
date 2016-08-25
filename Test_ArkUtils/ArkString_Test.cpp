#include "stdafx.h"
#include "CppUnitTest.h"

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
		}

	};
}