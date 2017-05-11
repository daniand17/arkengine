#include <Windows.h>
#include <iostream>
#include "Filestream.h"
#include "ArkDirectory.h"

ArkDirectory::ArkDirectory()
{
}


ArkStringList ArkDirectory::getEntryList(EntryTypes type) const
{

	switch ( type )
	{
	case ET_Files:
		return getFileList();
	case ET_Directories:
		return getFolderList();
	}
	return ArkStringList();
}



ArkStringList ArkDirectory::getFileList() const
{
	HANDLE handle = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA findFileData;

	ArkString firstFile = m_path;

	if ( m_path.charAt(m_path.length() - 1) != '/' )
		firstFile += "/*";
	else
		firstFile += "*";

	handle = FindFirstFile(firstFile.c_str(), &findFileData);
	ArkStringList fileList;
	do
	{
		if ( !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
		{
			ArkString filename(findFileData.cFileName);
			if ( filename != ArkString("..") )
			{
				fileList.push_back(filename);
			}
		}
	}
	while ( FindNextFile(handle, &findFileData) );
	return fileList;
}



ArkStringList ArkDirectory::getFolderList() const
{
	HANDLE handle = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA findFileData;

	ArkString firstFile = m_path;

	if ( m_path.charAt(m_path.length() - 1) != '/' )
		firstFile += "/*";
	else
		firstFile += "*";

	handle = FindFirstFile(firstFile.c_str(), &findFileData);
	ArkStringList fileList;
	do
	{
		if ( findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			ArkString filename(findFileData.cFileName);
			if ( filename != ArkString("..") )
			{
				fileList.push_back(filename);
			}
		}
	}
	while ( FindNextFile(handle, &findFileData) );
	return fileList;
}



ArkDirectory::ArkDirectory(ArkString path)
	: m_path(path)
{
}



bool ArkDirectory::exists() const
{
	return exists(m_path);
}



bool ArkDirectory::exists(ArkString path) const
{
	DWORD dwAttrib = GetFileAttributes(path.c_str());
	return dwAttrib != INVALID_FILE_ATTRIBUTES && dwAttrib & FILE_ATTRIBUTE_DIRECTORY;
}



void ArkDirectory::mkdir(ArkString dir) const
{
	if ( !exists(dir) )
	{
		CreateDirectory(dir.c_str(), NULL);
	}
}



void ArkDirectory::mkdir() const
{
	if ( exists() || m_path.length() == 0 ) return;
	mkdir(m_path);
}



void ArkDirectory::rmdir() const
{
	if ( exists() )
	{
		RemoveDirectory(m_path.c_str());
	}
}



void ArkDirectory::mkpath() const
{
	ArkStringList strList = m_path.split('\\');

	ArkStringList totalPath;

	for ( int i = 0 ; i < strList.size() ; i++ )
	{
		ArkStringList l = strList.at(i).split('/');

		for ( int k = 0 ; k < l.size() ; k++ )
		{
			totalPath.push_back(l.at(k));
		}
	}


	ArkString currPath("");
	for ( int i = 0 ; i < totalPath.size() ; i++ )
	{
		currPath += totalPath.at(i) + "\\";
		if ( !exists(currPath) )
		{
			mkdir(currPath);
		}
	}
}



ArkString ArkDirectory::getAbsolutePath() const
{
	char path[MAX_PATH];
	GetFullPathName(m_path.c_str(), MAX_PATH, path, NULL);

	ArkString p(path);
	if ( p.charAt(p.length() - 1) != '\\' )
		p += "\\";
	return p;
}