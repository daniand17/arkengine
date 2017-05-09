#include "stdafx.h"
#include "CppUnitTest.h"

#include <exception>

#include "ArkDirectory.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test_ArkUtils
{
	TEST_CLASS(ArkDirectory_Test)
	{

	public:
		TEST_METHOD(ArkDirectory_Existsa)
		{
			ArkDirectory dir("AndysTestProject");
			Assert::IsTrue(dir.exists());

			ArkDirectory anotherDir("Testandthingsandstuff");
			Assert::IsFalse(anotherDir.exists());
		}

		TEST_METHOD(ArkDirectory_NewDirectoryHasZeroFiles)
		{
			ArkDirectory dir("FileSystemTest");
			if ( !dir.exists() )
				dir.mkdir();

			Assert::IsTrue(dir.exists());

			Assert::AreEqual(static_cast<unsigned int>(0), dir.getFileCount());

			std::vector<ArkFile> const * fileList = dir.getFileList();

			Assert::AreEqual(static_cast<unsigned int>(0), fileList->size());

			dir.rmdir();
		}

		TEST_METHOD(ArkDirectory_ShouldDeleteDirectory)
		{
			ArkDirectory dir("DeleteDirectoryTest");

			if ( !dir.exists() )
				dir.mkdir();

			Assert::IsTrue(dir.exists());

			dir.rmdir();
			Assert::IsFalse(dir.exists());
		}

		TEST_METHOD(ArkDirectory_ShouldGetFileList)
		{

			ArkDirectory dir("AndysTestProject/meshes/");

			Assert::IsTrue(dir.exists());

			Assert::AreEqual(static_cast<unsigned int>(4), dir.getFileCount());
				
		}

		TEST_METHOD(ArkDirectory_ShouldReturnAbsolutePath)
		{
			ArkDirectory dir("AndysTestProject");
			Assert::IsTrue(dir.exists());
			// NOTE: IT's okay for this test to fail on other PC's for obvious reasons.
			ArkString expected("C:\\Users\\dania\\git\\arkengine.git\\ArkEngine\\x64\\Test\\AndysTestProject\\");

			Assert::AreEqual(expected.toStdString(), dir.getAbsolutePath().toStdString());

			ArkDirectory dir0("AndysTestProject/meshes");
			Assert::IsTrue(dir0.exists());
			Assert::AreEqual(expected.toStdString() + "meshes\\", dir0.getAbsolutePath().toStdString());
		}

		TEST_METHOD(ArkDirectory_FileExists)
		{
			ArkDirectory dir("AndysTestProject/meshes");
			Assert::IsTrue(dir.exists());

			Assert::IsTrue(dir.fileExists("cube.obj"));

			ArkFile * file = dir.getFileByFilename("cube.obj");
			Assert::IsTrue(file != NULL);

			Assert::IsFalse(dir.fileExists("hello stuff things"));
		}

		TEST_METHOD(ArkDirectory_CreateFile)
		{
			ArkDirectory dir("AndysTestProject/meta");
			dir.createFile("testFile", "test");

			Assert::IsTrue(dir.fileExists("testFile.test"));
		}
	};



	TEST_CLASS(ArkFile_Test)
	{
		TEST_METHOD(ArkFile_Extension)
		{
			ArkDirectory dir("AndysTestProject/meshes");
			Assert::IsTrue(dir.fileExists("cube.obj"));

			ArkFile * theFile = dir.getFileByFilename("cube.obj");
			Assert::AreEqual(theFile->getExtension().toStdString(), ArkString("obj").toStdString());
			Assert::AreEqual(theFile->getFilename().toStdString(), ArkString("cube.obj").toStdString());
		}

		TEST_METHOD(ArkFile_ReadContents)
		{
			ArkDirectory dir("AndysTestProject/materials");
			Assert::IsTrue(dir.exists());
			Assert::IsTrue(dir.fileExists("materials.meta"));
			
			ArkFile * materialFile = dir.getFileByFilename("materials.meta");
			ArkString contents = materialFile->readAll();
			Assert::IsTrue(contents.length() > 0);
			
			ArkStringList linelist = contents.split('\n');
			Assert::AreEqual(static_cast<unsigned int>(7), linelist.size());
		}
	};
}