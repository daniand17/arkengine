#pragma once

#include "Resource.h"
#include "BuildOptions.h"
#include "TextureInfo.h"

struct ShaderProgram : Resource
{
public:
	ShaderProgram(ArkString name, ArkString vertexShader, ArkString fragmentShader);

	void setTexture(TextureInfo * texture) { m_texture = texture; }
	GLuint getId() const { return m_programId; }
	GLuint getTextureId() const { return m_programId; }
	int numAttributes() const { return m_numAttributes; }
	int numUniforms() const { return m_numUniforms; }

	void setVertexShader(ArkString vertexShader) { m_vertexShader = vertexShader; }
	void setFragmentShader(ArkString vertexShader) { m_fragmentShader = m_fragmentShader; }
	void compileAndLoadShader();
	void unloadShader();

	ArkString getVertexShaderPath() const { return m_vertexShader; }
	ArkString getFragmentShaderPath() const { return m_fragmentShader; }
	ArkString getVertexShaderName() const { return m_vertexShader.split('\\').getLast(); }
	ArkString getFragmentShaderName() const { return m_fragmentShader.split('\\').getLast(); }

	// Inherited via Resource
	virtual void serialize(ArkString absFilepath) const override;
	virtual void deserialize(ArkString absFilepath) const override;

private:
	ArkString m_vertexShader;
	ArkString m_fragmentShader;
	GLuint m_programId;
	int m_numAttributes;
	int m_numUniforms;
	TextureInfo * m_texture;

	GLuint loadShaders(const char * vertex_file_path, const char * fragment_file_path);

	// Inherited via Resource
	virtual ArkString getResourceFileExtension() const override;
};