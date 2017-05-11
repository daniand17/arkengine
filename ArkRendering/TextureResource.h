#pragma once
#include "BuildOptions.h"
#include "ArkString.h"
#include "ProjectResource.h"


class TextureResource : public ProjectResource
{
public:
	TextureResource(ArkString name, ArkString filename);
	~TextureResource() { glDeleteTextures(1, &m_textureId); }

private:
	GLuint m_textureId;
	GLuint loadBMP_custom(char const * as);

	// Inherited via ProjectResource
	virtual void serialize() const override;
	virtual void deserialize() override;
};
