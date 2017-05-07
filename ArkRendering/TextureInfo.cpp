#include "TextureInfo.h"
#include "ImageLoader.h"

TextureInfo::TextureInfo(ArkString filename)
	: mTextureId(0)
{
	mTextureId = loadBMP_custom(filename.c_str());
}
