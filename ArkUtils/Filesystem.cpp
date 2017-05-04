#include <Windows.h>
#include <iostream>
#include "Filesystem.h"
#include "Filestream.h"

ArkFile::ArkFile(ArkString directory, ArkString name)
	: m_contents("")
	, m_filename(name)
	, m_path(directory)
{
	if ( m_path.charAt(m_path.length() - 1) != '\\' )
		m_path += "\\";
}



ArkString ArkFile::getFileContents() const
{
	Filestream filestream(m_path + m_filename);
	filestream.OpenFile(Filestream::Read);

	ArkString fileContents("");
	filestream.ReadAll(&fileContents);

	filestream.CloseFile();

	return fileContents;
}



ArkString ArkFile::getExtension() const
{
	ArkStringList list = m_filename.split('.');
	if ( list.size() > 1 )

		return list.at(list.size() - 1);
	return ArkString("");
}



void ArkFile::writeToFile(ArkString contents)
{
	ArkString path = m_path;

	if ( path.charAt(path.length() - 1) != '\\' )
		path += "\\";

	Filestream filestream(path + m_filename);
	filestream.OpenFile(Filestream::FileOpenType::Write);
	filestream.WriteStringToFile(contents);
	filestream.CloseFile();
}



ArkDirectory::ArkDirectory()
{
}



ArkDirectory::ArkDirectory(ArkString path)
	: m_path(path)
{
	if ( exists() )
		populateFileList();
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



bool ArkDirectory::fileExists(ArkString filename) const
{
	for ( unsigned int i = 0 ; i < m_filelist.size() ; i++ )
		if ( m_filelist[i].getFilename() == filename )
			return true;

	return false;
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



void ArkDirectory::mkPath() const
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



ArkFile * ArkDirectory::getFileByFilename(ArkString filename)
{
	for ( unsigned int i = 0 ; i < m_filelist.size() ; i++ )
		if ( m_filelist[i].getFilename() == filename )
			return &m_filelist[i];

	return NULL;
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



void ArkDirectory::populateFileList()
{
	HANDLE handle = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA findFileData;

	ArkString firstFile = m_path;

	if ( m_path.charAt(m_path.length() - 1) != '/' )
		firstFile += "/*";
	else
		firstFile += "*";

	handle = FindFirstFile(firstFile.c_str(), &findFileData);

	do
	{
		if ( !(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
		{
			ArkString filename(findFileData.cFileName);
			if ( filename != ArkString("..") )
				m_filelist.push_back(ArkFile(m_path, filename));
		}
	}
	while ( FindNextFile(handle, &findFileData) );
}



ArkFile * ArkDirectory::createFile(ArkString name, ArkString extension)
{
	ArkFile file(getAbsolutePath(), name + "." + extension);

	file.writeToFile("");

	m_filelist.push_back(file);

	return &m_filelist.at(m_filelist.size() - 1);
}