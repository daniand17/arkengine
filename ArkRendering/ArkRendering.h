#pragma once
#include <vector>

#include "Vec2.h"
#include "Vec3.h"
#include "BuildOptions.h"
#include "ArkString.h"
#include "Mat4.h"

typedef size_t Resource_Id;

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
		Resource_Id id;

		Vec3 eyePosition;
		Vec3 color;

		void bindLightToShader() const;
		void getUniformLocationsFromShader(GLuint shaderProgramId);

	private:
		GLuint eyeId;
		GLuint colId;
	};

	struct Resource
	{
		Resource_Id id;
	};

	struct MaterialInfo : Resource
	{
		Vec3 ambient;
		Vec3 diffuse;
		Vec3 specular;
		float shininess;
		
		void setShaderProgram(GLuint shaderProgram);
		void UseShaderProgram() const;
		GLuint GetShaderProgramId() const { return mShaderProgram; }

	private:
		GLuint mShaderProgram;
		GLuint shiId;
		GLuint ambId;
		GLuint difId;
		GLuint spcId;
	};

	struct CameraInfo
	{
		Mat4 projectionMatrix;
		Mat4 viewMatrix;
	};

	struct MeshInfo : Resource
	{
		std::vector<Vec3> vertices;
		std::vector<Vec3> normals;
		std::vector<Vec2> uvs;
	};

	struct ModelInfo : Resource
	{
		ModelInfo() 
			: materialId(0)
			, meshId(0)
		{}

		Resource_Id materialId;
		Resource_Id meshId;
		Mat4 modelMatrix = Mat4::identity();
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