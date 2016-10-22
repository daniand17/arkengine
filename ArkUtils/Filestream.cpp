#include "Filestream.h"
#include "ArkDebug.h"

Filestream::Filestream(ArkString filepath)
	: mPath(filepath)
	, mOpenType(FileOpenType::Read)
{
}

Filestream::Filestream(ArkString filename, ArkString extension)
{
	mPath = filename + "." + extension;
}

int Filestream::OpenFile(FileOpenType type)
{
	if ( type < 0 || type > FileOpenType::NumTypes )
		return -1;

	mOpenType = type;
	switch ( type )
	{
	case FileOpenType::Read:
		mFileStream.open(mPath.c_str(), std::ios::in);
		break;
	case FileOpenType::Write:
		mFileStream.open(mPath.c_str(), std::ios::out);
		break;
	case FileOpenType::ReadWrite:
		mFileStream.open(mPath.c_str(), std::ios::out | std::ios::out);
		break;
	}

	if ( mFileStream.fail() )
		throw FailBit;
	else if ( mFileStream.bad() )
		throw BadBit;
	else if ( mFileStream.eof() )
		throw Eof;

	return GoodBit;
}

void Filestream::CloseFile()
{
	if ( mFileStream.is_open() )
		mFileStream.close();
}

void Filestream::ReadAll(ArkString * outContents)
{
	if ( mOpenType == FileOpenType::ReadWrite || mOpenType == FileOpenType::Read )
	{
		std::string line;
		bool previousLine = false;
		while ( std::getline(mFileStream, line) )
		{
			if ( previousLine )
				*outContents += "\n";

			*outContents += ArkString(line);
			previousLine = true;
		}
	}
}

void Filestream::WriteStringToFile(ArkString * stringToWrite)
{
	_ASSERTE(mFileStream.is_open());

	if ( mFileStream.is_open() )
		mFileStream.write(stringToWrite->c_str(), stringToWrite->length());
}

void Filestream::WriteStringToFile(ArkString & stringToWrite)
{
	_ASSERTE(mFileStream.is_open());

	if ( mFileStream.is_open() )
		mFileStream.write(stringToWrite.c_str(), stringToWrite.length());
}
