#include "Filestream.h"
#include "ArkDebug.h"

Filestream::Filestream(ArkString filepath)
	: m_path(filepath)
	, m_openType(FileOpenType::Read)
{
}



Filestream::Filestream(ArkString filename, ArkString extension)
{
	m_path = filename + "." + extension;
}



int Filestream::openFile(FileOpenType type)
{
	if ( type < 0 || type > FileOpenType::NumTypes )
		return -1;

	m_openType = type;
	switch ( type )
	{
	case FileOpenType::Read:
		m_filestream.open(m_path.c_str(), std::ios::in);
		break;
	case FileOpenType::Write:
		m_filestream.open(m_path.c_str(), std::ios::out);
		break;
	case FileOpenType::ReadWrite:
		m_filestream.open(m_path.c_str(), std::ios::out | std::ios::out);
		break;
	}

	if ( m_filestream.is_open() )
	{
		if ( m_filestream.fail() )
			throw FailBit;
		else if ( m_filestream.bad() )
			throw BadBit;
		else if ( m_filestream.eof() )
			throw Eof;
	}
	return GoodBit;
}



void Filestream::closeFile()
{
	if ( m_filestream.is_open() )
		m_filestream.close();
}



void Filestream::readAll(ArkString * outContents)
{
	if ( m_openType == FileOpenType::ReadWrite || m_openType == FileOpenType::Read )
	{
		std::string line;
		bool previousLine = false;
		while ( std::getline(m_filestream, line) )
		{
			if ( previousLine )
				*outContents += "\n";

			*outContents += ArkString(line);
			previousLine = true;
		}
	}
}



void Filestream::writeToFile(ArkString * stringToWrite)
{
	_ASSERTE(m_filestream.is_open());

	if ( m_filestream.is_open() )
		m_filestream.write(stringToWrite->c_str(), stringToWrite->length());
}



void Filestream::writeToFile(ArkString & stringToWrite)
{
	_ASSERTE(m_filestream.is_open());

	if ( m_filestream.is_open() )
		m_filestream.write(stringToWrite.c_str(), stringToWrite.length());
}
