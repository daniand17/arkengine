#pragma once
#include "Vec3.h"
#include "BuildOptions.h"
#include "ArkString.h"

namespace ArkRendering
{
	enum LightType
	{
		Point,
		Directional,
		Spot
	};

	struct LightInfo
	{
		LightType type;
		Vec3 worldPosition;
		Vec3 direction;
		Vec3 color;

		float lightPower;
	};

	struct MaterialInfo
	{
		float ka;
		float kd;
		float ks;
		float shininess;
	};

	class Texture
	{
	public:
		Texture(ArkString filename);
		~Texture() { glDeleteTextures(1, &mTextureId); }

	private:
		GLuint mTextureId;
	};

	class ShaderProgram
	{
	public:
		ShaderProgram(ArkString vertexShader, ArkString fragmentShader);
		~ShaderProgram() { glDeleteProgram(mProgramId); delete mTexture; } // TODO (AD) probably not a great place for this 
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
}