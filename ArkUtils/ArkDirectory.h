#pragma once
#include <vector>

#include "ArkString.h"
#include "ArkFile.h"

class ArkDirectory
{
public:
	enum EntryTypes
	{
		ET_Files,
		ET_Directories
	};

	ArkDirectory();
	ArkDirectory(ArkString path);

	ArkStringList getEntryList(EntryTypes type) const;

	bool exists() const;
	
	void mkdir() const;
	void rmdir() const;
	void mkpath() const;
	
	ArkString getAbsolutePath() const;
	ArkString getRelativePath() const { return m_path; }

private:

	ArkString m_path;

	bool exists(ArkString path) const;
	void mkdir(ArkString dir) const;

	ArkStringList getFileList() const;
	ArkStringList getFolderList() const;


};	