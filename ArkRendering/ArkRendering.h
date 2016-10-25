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
		virtual ArkString Synchronize() const = 0;
	};

	class Texture
	{
	public:
		Texture(ArkString filename);
		~Texture() { glDeleteTextures(1, &mTextureId); }

	private:
		GLuint mTextureId;
	};

	struct ShaderProgram : Resource
	{
	public:
		ShaderProgram(ArkString vertexShader, ArkString fragmentShader);
		~ShaderProgram() {} // TODO (AD) probably not a great place for this 
		void setTexture(Texture * texture) { mTexture = texture; }
		GLuint getId() const { return mProgramId; }
		GLuint getTextureId() const { return mProgramId; }
		int numAttributes() const { return mNumAttributes; }
		int numUniforms() const { return mNumUniforms; }

		ArkString Synchronize() const override;

		void setVertexShader(ArkString vertexShader) { m_vertexShader = vertexShader; }
		void setFragmentShader(ArkString vertexShader) { m_fragmentShader = m_fragmentShader; }

		void compileAndLoadShader();
		void unloadShader();

		ArkString getVertexShader() const { return m_vertexShader; }
		ArkString getFragmentShader() const { return m_fragmentShader; }

	private:
		ArkString m_vertexShader;
		ArkString m_fragmentShader;
		GLuint mProgramId;
		int mNumAttributes;
		int mNumUniforms;
		Texture * mTexture;
	};

	struct MaterialInfo : Resource
	{
		Vec3 ambient;
		Vec3 diffuse;
		Vec3 specular;
		float shininess;

		MaterialInfo();

		void setShaderProgramId(Resource_Id shaderProgramId) { m_shaderProgramId = shaderProgramId; }
		void setShaderProgram(ArkRendering::ShaderProgram * shaderProgram, bool bind = true);
		void UseShaderProgram() const;
		
		ArkRendering::ShaderProgram * getShaderProgram() const { return m_shaderProgram; }

		Resource_Id getShaderProgramId() const { return m_shaderProgramId; }

		ArkString Synchronize() const override;

	private:
		Resource_Id m_shaderProgramId;
		ArkRendering::ShaderProgram * m_shaderProgram;
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
		ArkString name;
		std::vector<Vec3> vertices;
		std::vector<Vec3> normals;
		std::vector<Vec2> uvs;

		ArkString Synchronize() const override;
	};

	struct ModelInfo : Resource
	{
		ModelInfo()
			: materialId(0)
			, meshId(0)
		{
		}

		Resource_Id materialId;
		Resource_Id meshId;
		Mat4 modelMatrix = Mat4::identity();

		ArkString Synchronize() const override;
	};
}