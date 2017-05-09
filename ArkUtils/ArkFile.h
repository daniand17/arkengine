#pragma once

#include "ArkString.h"

class ArkFile
{
public:
	ArkFile(ArkString path);
	ArkString readAll() const;
	ArkString getPath() const { return m_path; }

	void writeToFile(ArkString contents) const;
	bool exists() const;
	void mkfile() const;

private:
	ArkString m_contents;
	ArkString m_path;
};