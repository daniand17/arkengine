
#include "TextureResource.h"

TextureResource::TextureResource(ArkString name, ArkString filename)
	: ProjectResource(name, filename, RT_Texture)
	, m_textureId(0)
{
}



GLuint TextureResource::loadBMP_custom(char const * filename)
{
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
							  // Actual RGB data
	unsigned char * data;

	FILE * file;

	fopen_s(&file, filename, "rb");

	if ( !file )
	{
		printf("Image could not be opened\n");
		return 0;
	}

	if ( fread(header, 1, 54, file) != 54 )
	{
		printf("Not a correct BMP file\n");
		return false;
	}

	if ( header[0] != 'B' || header[1] != 'M' )
	{
		printf("Not a correct BMP file\n");
		return 0;
	}

	dataPos = *(int *)&(header[0x0A]);
	imageSize = *(int *)&(header[0x22]);
	width = *(int *)&(header[0x12]);
	height = *(int *)&(header[0x16]);

	if ( !imageSize ) imageSize = width * height * 3;
	if ( !dataPos ) dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}



void TextureResource::serialize() const
{
}



void TextureResource::deserialize()
{
	m_textureId = loadBMP_custom(m_filename.c_str());
}
