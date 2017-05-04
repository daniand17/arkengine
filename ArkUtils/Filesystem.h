#pragma once
#include <vector>

#include "ArkString.h"

class ArkFile
{
public:
	ArkFile(ArkString directory, ArkString name);
	ArkString getFileContents() const;
	ArkString getFilename() const { return m_filename; }
	ArkString getExtension() const;
	
	void writeToFile(ArkString contents);

private:
	ArkString m_contents;
	
	ArkString m_filename;
	ArkString m_path;
};

////////////////////////////////////////////////////////////////////////////////////////////////

class ArkDirectory
{

public:
	ArkDirectory();
	ArkDirectory(ArkString path);

	std::vector<ArkFile> const * getFileList() const { return &m_filelist; }
	bool exists() const;
	bool fileExists(ArkString filename) const;
	
	void mkdir() const;
	void rmdir() const;
	void mkPath() const;
	
	ArkFile * getFileByFilename(ArkString filename);
	ArkFile * createFile(ArkString name, ArkString extension);

	ArkString getAbsolutePath() const;
	ArkString getRelativePath() const { return m_path; }

	size_t getFileCount() const { return m_filelist.size(); }

private:
	void populateFileList();
	std::vector<ArkFile> m_filelist;

	ArkString m_path;

	bool exists(ArkString path) const;
	void mkdir(ArkString dir) const;
};