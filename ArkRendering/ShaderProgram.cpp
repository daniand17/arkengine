#include "ShaderProgram.h"
#include "ShaderProgram.h"
#include <fstream>

#include <vector>

ShaderProgram::ShaderProgram()
	: m_programId(0)
{
}



void ShaderProgram::compileAndLoadShader(ArkString const & vertexSource, ArkString const & fragmentSource)
{
	m_programId = loadShaders(vertexSource.c_str(), fragmentSource.c_str());

	doProgramIntrospection(GL_PROGRAM_INPUT, m_attribMap);
	doProgramIntrospection(GL_UNIFORM, m_uniformMap);
}


// NOTE: Code to get more info about a shaders attrs http://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shade
void ShaderProgram::doProgramIntrospection(GLint queryItem, std::map<ArkString, PropertyInfo> & theMap)
{
	GLint count = 0;
	glGetProgramInterfaceiv(m_programId, queryItem, GL_ACTIVE_RESOURCES, &count);
	std::vector<GLenum> properties;
	properties.push_back(GL_NAME_LENGTH);
	properties.push_back(GL_TYPE);
	properties.push_back(GL_ARRAY_SIZE);
	std::vector<GLint> values(properties.size());
	std::vector<GLchar> nameData(256);


	for ( GLuint i = 0 ; i < count ; i++ )
	{
		glGetProgramResourceiv(m_programId, queryItem, i, properties.size(), &properties[0], values.size(), NULL, &values[0]);

		nameData.resize(values[0]);
		glGetProgramResourceName(m_programId, queryItem, i, nameData.size(), NULL, &nameData[0]);
		ArkString propName((char *) &(nameData[0]));

		PropertyInfo pInfo;
		pInfo.type = mapGLTypeToArkType(values[1]);
		if ( queryItem == GL_PROGRAM_INPUT )
		{
			pInfo.location = glGetAttribLocation(m_programId, propName.c_str());
		}
		else
		{
			pInfo.location = glGetUniformLocation(m_programId, propName.c_str());
		}
		theMap.insert(std::pair<ArkString, PropertyInfo>(propName, pInfo));
	}
}



ShaderProgram::PropertyTypes ShaderProgram::mapGLTypeToArkType(const GLint &val)
{
	switch ( val )
	{
	case GL_FLOAT:			return PT_Float;
	case GL_FLOAT_VEC2:		return PT_Vec2f;
	case GL_FLOAT_VEC3:		return PT_Vec3f;
	case GL_FLOAT_VEC4:		return PT_Vec4f;
	case GL_FLOAT_MAT2:		return PT_Mat2f;
	case GL_FLOAT_MAT3:		return PT_Mat3f;
	case GL_FLOAT_MAT4:		return PT_Mat4f;
	case GL_FLOAT_MAT2x3:
		break;
	case GL_FLOAT_MAT2x4:
		break;
	case GL_FLOAT_MAT3x2:
		break;
	case GL_FLOAT_MAT3x4:
		break;
	case GL_FLOAT_MAT4x2:
		break;
	case GL_FLOAT_MAT4x3:
		break;
	case GL_INT:			return PT_Int;
	case GL_INT_VEC2:		return PT_Vec2f;
	case GL_INT_VEC3:		return PT_Vec3f;
	case GL_INT_VEC4:		return PT_Vec4f;
		break;
	case GL_UNSIGNED_INT:		return PT_Uint;
	case GL_UNSIGNED_INT_VEC2:	return PT_Vec2f;
	case GL_UNSIGNED_INT_VEC3:	return PT_Vec3f;
	case GL_UNSIGNED_INT_VEC4:	return PT_Vec4f;
	case GL_DOUBLE:				return PT_Double;

	case GL_DOUBLE_VEC2:
		break;
	case GL_DOUBLE_VEC3:
		break;
	case GL_DOUBLE_VEC4:
		break;
	case GL_DOUBLE_MAT2:		return PT_Mat2f;
	case GL_DOUBLE_MAT3:		return PT_Mat3f;
	case GL_DOUBLE_MAT4:		return PT_Mat4f;
	case GL_DOUBLE_MAT2x3:
		break;
	case GL_DOUBLE_MAT2x4:
		break;
	case GL_DOUBLE_MAT3x2:
		break;
	case GL_DOUBLE_MAT3x4:
		break;
	case GL_DOUBLE_MAT4x2:
		break;
	case GL_DOUBLE_MAT4x3:
		break;
	}

	return PT_Unsupported;
}



void ShaderProgram::unloadShader()
{
	glDeleteProgram(m_programId);
}



GLuint ShaderProgram::loadShaders(const char * vertexSource, const char * fragmentSource)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertexSource);
	glShaderSource(VertexShaderID, 1, &vertexSource, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragmentSource);
	glShaderSource(FragmentShaderID, 1, &fragmentSource, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}