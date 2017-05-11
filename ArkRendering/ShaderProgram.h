#pragma once

#include "ProjectResource.h"
#include "BuildOptions.h"
#include "TextureResource.h"
#include <map>

struct ShaderProgram
{
public:
	enum PropertyTypes
	{
		PT_Unsupported = -1,

		PT_Float,
		PT_Int,
		PT_Uint,
		PT_Double,

		PT_Vec2f,
		PT_Vec3f,
		PT_Vec4f,

		PT_Mat2f,
		PT_Mat3f,
		PT_Mat4f,

		PT_NumTypes
	};

	ShaderProgram();

	GLuint getId() const { return m_programId; }
	GLuint getTextureId() const { return m_programId; }

	void compileAndLoadShader(ArkString const & vertexSource, ArkString const & fragmentSource);
	void unloadShader();

private:
	struct PropertyInfo
	{
		GLuint location;
		PropertyTypes type;
	};

	GLuint m_programId;
	std::map<ArkString, PropertyInfo> m_attribMap;
	std::map<ArkString, PropertyInfo> m_uniformMap;

	GLuint loadShaders(const char * vertex_file_path, const char * fragment_file_path);
	PropertyTypes mapGLTypeToArkType(const GLint &val);
	void doProgramIntrospection(GLint queryItem, std::map<ArkString, PropertyInfo> & theMap);
};