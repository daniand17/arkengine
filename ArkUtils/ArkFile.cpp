#include <Windows.h>
#include <iostream>

#include "ArkFile.h"
#include "Filestream.h"

ArkFile::ArkFile(ArkString path)
	: m_contents("")
	, m_path(path)
{

}



ArkString ArkFile::getFileContents() const
{
	Filestream filestream(m_path);
	filestream.openFile(Filestream::Read);

	ArkString fileContents("");
	filestream.readAll(&fileContents);

	filestream.closeFile();

	return fileContents;
}



void ArkFile::writeToFile(ArkString contents) const
{
	Filestream filestream(m_path);
	if ( filestream.openFile(Filestream::FileOpenType::Write) )
	{
		filestream.writeToFile(contents);
		filestream.closeFile();
	}
}



bool ArkFile::exists() const
{
	return INVALID_FILE_ATTRIBUTES != GetFileAttributes(m_path.c_str())
		&& GetLastError() != ERROR_FILE_NOT_FOUND;
}



void ArkFile::mkfile() const
{
	writeToFile("");
}