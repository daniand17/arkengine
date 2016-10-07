#pragma once
#include "BuildOptions.h"
#include "ArkString.h"

namespace RendererUtils
{
	class Texture
	{
	public:
		Texture(ArkString filename);
		~Texture() { glDeleteTextures(1, &mTextureId); }

	private:
		GLuint mTextureId;
	};

	class ArkShaderProgram
	{
	public:
		ArkShaderProgram(ArkString vertexShader, ArkString fragmentShader);
		~ArkShaderProgram() { glDeleteProgram(mProgramId); delete mTexture; } // TODO (AD) probably not a great place for this 
		void setTexture(Texture * texture) { mTexture = texture; }
		GLuint getId() const { return mProgramId; }
		GLuint getTextureId() const { return mProgramId; }
		int numAttributes() const { return mNumAttributes; }
		int numUniforms() const { return mNumUniforms; }

	private:
		GLuint mProgramId;
		int mNumAttributes;
		int mNumUniforms;
		Texture * mTexture;
	};
};