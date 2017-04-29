#pragma once
#include <map>

#include "ArkRendering.h"
#include "AbstractResourceFactory.h"

class ShaderFactory : public ResourceFactory
{
public:
	void deserializeResources() override;
	void serializeResources() override;
	unsigned int ShaderFactory::size() const override { return m_loadedShaders.size(); }
	void clear() override;
	ArkRendering::ShaderProgram * getResourceByName(ArkString name) override;

	void compileShaders();
	void CreateShader(ArkString shaderName, ArkString vertexShader, ArkString fragmentShader);

private:
	typedef std::map<ArkString, ArkRendering::ShaderProgram *> ShaderCollection;
	typedef std::pair<ArkString, ArkRendering::ShaderProgram *> ShaderNamePair;
	ShaderCollection m_loadedShaders;

	void createShaderFromString(ArkString string);

};