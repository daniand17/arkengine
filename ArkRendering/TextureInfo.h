#pragma once
#include "BuildOptions.h"
#include "ArkString.h"

class TextureInfo
{
public:
	TextureInfo(ArkString filename);
	~TextureInfo() { glDeleteTextures(1, &mTextureId); }

private:
	GLuint mTextureId;
};
