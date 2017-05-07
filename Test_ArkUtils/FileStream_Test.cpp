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
				result = filestream.openFile(Filestream::FileOpenType::Read);
			}
			catch ( std::exception & e )
			{
				e.what();
			}

			Assert::IsTrue(result == Filestream::FileReadResult::GoodBit);

			filestream.closeFile();
		}

		TEST_METHOD(ReadFile)
		{
			Filestream filestream("TestInput.txt");

			try
			{
				filestream.openFile(Filestream::FileOpenType::Read);
			}
			catch ( std::exception & e ) { e.what(); }

			ArkString contents;
			filestream.readAll(&contents);
			Assert::AreEqual(ArkString("Hello World").toStdString(), contents.toStdString());
		}

		TEST_METHOD(WriteToFileAndReadBack)
		{
			Filestream stream("WriteToFileAndReadBackTest", "txt");

			try { stream.openFile(Filestream::FileOpenType::Write); }
			catch ( std::exception & e ) { e.what(); }

			ArkString stuffToWrite("Goodbye cruel world!");
			stream.writeToFile(&stuffToWrite);
			stream.closeFile();

			Filestream istream("WriteToFileAndReadBackTest", "txt");
			try { istream.openFile(Filestream::FileOpenType::Read); }
			catch ( std::exception & e ) { e.what(); }

			ArkString stuffToRead;
			istream.readAll(&stuffToRead);
			istream.closeFile();
			Assert::AreEqual(stuffToWrite.toStdString(), stuffToRead.toStdString());
		}

		TEST_METHOD(WriteToFileMultipleLinesAndReadBack)
		{
			Filestream ofilestream("ManyLinesWriteAndRead", "txt");

			try { ofilestream.openFile(Filestream::FileOpenType::Write); }
			catch ( std::exception & e ) { e.what(); }

			ArkString stringtowrite("Hello world\nGoodbye world");

			ofilestream.writeToFile(stringtowrite);
			ofilestream.closeFile();

			Filestream ifilestream("ManyLinesWriteAndRead", "txt");
			try { ifilestream.openFile(Filestream::FileOpenType::Read); }
			catch ( std::exception & e ) { e.what(); }

			ArkString result("");
			ifilestream.readAll(&result);
			ifilestream.closeFile();

			Assert::AreEqual(stringtowrite.toStdString(), result.toStdString());
		}
	};
}