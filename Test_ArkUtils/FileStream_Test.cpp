#include "stdafx.h"
#include "CppUnitTest.h"

#include <exception>

#include "ArkString.h"
#include "Filestream.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test_ArkUtils
{
	TEST_CLASS(Filestream_Test)
	{
	public:

		TEST_METHOD(Constructor)
		{
			Filestream filestream("TestInput.txt");

			int result = 0;
			try
			{
				result = filestream.OpenFile(Filestream::FileOpenType::Read);
			}
			catch ( std::exception & e )
			{
				e.what();
			}

			Assert::IsTrue(result == Filestream::FileReadResult::GoodBit);

			filestream.CloseFile();
		}

		TEST_METHOD(ReadFile)
		{
			Filestream filestream("TestInput.txt");

			try
			{
				filestream.OpenFile(Filestream::FileOpenType::Read);
			}
			catch ( std::exception & e ) { e.what(); }

			ArkString contents;
			filestream.ReadAll(&contents);
			Assert::AreEqual(ArkString("Hello World").toStdString(), contents.toStdString());
		}

		TEST_METHOD(WriteToFileAndReadBack)
		{
			Filestream stream("WriteToFileAndReadBackTest", "txt");

			try { stream.OpenFile(Filestream::FileOpenType::Write); }
			catch ( std::exception & e ) { e.what(); }

			ArkString stuffToWrite("Goodbye cruel world!");
			stream.WriteStringToFile(&stuffToWrite);
			stream.CloseFile();

			Filestream istream("WriteToFileAndReadBackTest", "txt");
			try { istream.OpenFile(Filestream::FileOpenType::Read); }
			catch ( std::exception & e ) { e.what(); }

			ArkString stuffToRead;
			istream.ReadAll(&stuffToRead);
			istream.CloseFile();
			Assert::AreEqual(stuffToWrite.toStdString(), stuffToRead.toStdString());
		}

		TEST_METHOD(WriteToFileMultipleLinesAndReadBack)
		{
			Filestream ofilestream("ManyLinesWriteAndRead", "txt");

			try { ofilestream.OpenFile(Filestream::FileOpenType::Write); }
			catch ( std::exception & e ) { e.what(); }

			ArkString stringtowrite("Hello world\nGoodbye world");

			ofilestream.WriteStringToFile(stringtowrite);
			ofilestream.CloseFile();

			Filestream ifilestream("ManyLinesWriteAndRead", "txt");
			try { ifilestream.OpenFile(Filestream::FileOpenType::Read); }
			catch ( std::exception & e ) { e.what(); }

			ArkString result("");
			ifilestream.ReadAll(&result);
			ifilestream.CloseFile();

			Assert::AreEqual(stringtowrite.toStdString(), result.toStdString());
		}
	};
}