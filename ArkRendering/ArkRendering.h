#pragma once
#include <vector>

#include "Vec2.h"
#include "Vec3.h"
#include "BuildOptions.h"
#include "ArkString.h"
#include "Mat4.h"

typedef unsigned int Resource_Id;

namespace ArkRendering
{
	struct CameraInfo
	{
		Mat4 projectionMatrix;
		Mat4 viewMatrix;
	};


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

	class Texture
	{
	public:
		Texture(ArkString filename);
		~Texture() { glDeleteTextures(1, &mTextureId); }

	private:
		GLuint mTextureId;
	};

	struct Resource
	{
		ArkString m_name;
		virtual ArkString serialize() const = 0;
	};

	////////////////////////////////////////

	struct ShaderProgram : Resource
	{
	public:
		ShaderProgram(ArkString name, ArkString vertexShader, ArkString fragmentShader);
		~ShaderProgram() {} // TODO (AD) probably not a great place for this 
		void setTexture(Texture * texture) { m_texture = texture; }
		GLuint getId() const { return m_programId; }
		GLuint getTextureId() const { return m_programId; }
		int numAttributes() const { return m_numAttributes; }
		int numUniforms() const { return m_numUniforms; }

		ArkString serialize() const override;

		void setVertexShader(ArkString vertexShader) { m_vertexShader = vertexShader; }
		void setFragmentShader(ArkString vertexShader) { m_fragmentShader = m_fragmentShader; }
		void compileAndLoadShader();
		void unloadShader();

		ArkString getVertexShaderPath() const { return m_vertexShader; }
		ArkString getFragmentShaderPath() const { return m_fragmentShader; }
		ArkString getVertexShaderName() const { return m_vertexShader.split('\\').getLast(); }
		ArkString getFragmentShaderName() const { return m_fragmentShader.split('\\').getLast(); }

	private:
		ArkString m_vertexShader;
		ArkString m_fragmentShader;
		GLuint m_programId;
		int m_numAttributes;
		int m_numUniforms;
		Texture * m_texture;
	};

	////////////////////////////////////////

	struct MaterialInfo : Resource
	{
		Vec3 ambient;
		Vec3 diffuse;
		Vec3 specular;
		float shininess;

		MaterialInfo();

		void setShader(ArkString shader) { m_shaderName = shader; }
		void setShaderProgram(ArkRendering::ShaderProgram * shaderProgram);
		void useShaderProgram() const;

		void pushValuesToRenderer() const;
		void getVertexBindingsFromShader();

		ArkRendering::ShaderProgram * getShaderProgram() const { return m_shaderProgram; }

		ArkString getShaderName() const { return m_shaderName; }

		ArkString serialize() const override;

	private:
		ArkString m_shaderName;
		ArkRendering::ShaderProgram * m_shaderProgram;
		bool m_bound;
		GLuint shiId;
		GLuint ambId;
		GLuint difId;
		GLuint spcId;
	};

	////////////////////////////////////////

	struct MeshInfo : Resource
	{
		ArkString name;
		std::vector<Vec3> vertices;
		std::vector<Vec3> normals;
		std::vector<Vec2> uvs;

		ArkString serialize() const override;
	};

	////////////////////////////////////////

	struct ModelInfo : Resource
	{
		ModelInfo()
			: m_material("")
			, m_mesh("")
			, modelMatrix(Mat4::identity())
		{
		}

		ArkString m_material;
		ArkString m_mesh;
		Mat4 modelMatrix;

		ArkString serialize() const override;
	};
}