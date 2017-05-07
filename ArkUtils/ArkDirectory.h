#pragma once
#include <vector>

#include "ArkString.h"
#include "ArkFile.h"

class ArkDirectory
{

public:
	ArkDirectory();
	ArkDirectory(ArkString path);

	ArkStringList getFileList() const;
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
};