#pragma once
#include "BuildOptions.h"
#include "ArkString.h"
#include "Resource.h"


class TextureInfo : Resource
{
public:
	TextureInfo(ArkString filename);
	~TextureInfo() { glDeleteTextures(1, &mTextureId); }

private:
	GLuint mTextureId;
	// Inherited via Resource
	virtual void serialize(ArkString absFilepath) const override;
	virtual void deserialize(ArkString absFilepath) const override;

	GLuint loadBMP_custom(char const * as);
};
