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

	int openFile(FileOpenType type);
	void closeFile();
	bool isOpen() const { return m_filestream.is_open(); }

	void readAll(ArkString * outContents);

	void writeToFile(ArkString * stringToWrite);
	void writeToFile(ArkString & stringToWrite);

private:

	FileOpenType m_openType;
	ArkString m_path;

	std::fstream m_filestream;

};