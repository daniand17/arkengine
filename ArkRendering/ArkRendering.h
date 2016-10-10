#pragma once
#include <vector>

#include "Vec2.h"
#include "Vec3.h"
#include "BuildOptions.h"
#include "ArkString.h"
#include "Mat4.h"

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
		Vec3 eyePosition;
		Vec3 color;

		void bindLightToShader() const;
		void getUniformLocationsFromShader(GLuint shaderProgramId);

	private:
		GLuint eyeId;
		GLuint colId;
	};

	struct MeshInfo
	{
		std::vector<Vec3> vertices;
		std::vector<Vec3> normals;
		std::vector<Vec2> uvs;
	};

	struct MaterialInfo
	{
		Vec3 ambient;
		Vec3 diffuse;
		Vec3 specular;
		float shininess;

		void getUniformLocationsFromShader(GLuint shaderProgramId);
		void bindMaterialToShader() const;
	private:
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

	struct ModelInfo
	{
		unsigned int id;
		MaterialInfo * material;
		MeshInfo * mesh;
		Mat4 modelMatrix;
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