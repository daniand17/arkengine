#pragma once

#include <iostream>
#include <fstream>

#include "ArkString.h"

class Filestream
{
public:
	enum FileOpenType
	{
		Read,
		Write,
		ReadWrite,
		NumTypes
	};

	enum FileReadResult
	{
		FailBit,
		BadBit,
		GoodBit,
		Eof
	};

	Filestream(ArkString filepath);
	Filestream(ArkString filename, ArkString extension);

	int OpenFile(FileOpenType type);
	void CloseFile();
	bool IsOpen() const { return mFileStream.is_open(); }

	void ReadAll(ArkString * outContents);

	void WriteStringToFile(ArkString * stringToWrite);
	void WriteStringToFile(ArkString & stringToWrite);

private:

	FileOpenType mOpenType;
	ArkString mPath;

	std::fstream mFileStream;

};