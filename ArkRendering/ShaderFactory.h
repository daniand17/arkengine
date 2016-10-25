#pragma once
#include <vector>

#include "ArkRendering.h"
#include "AbstractResourceFactory.h"

class ShaderFactory : public ResourceFactory
{
public:
	Resource_Id CreateShader(ArkString vertexShader, ArkString fragmentShader);
	ArkRendering::ShaderProgram * GetShaderProgramByResourceId(Resource_Id programId) const;

	void DesynchronizeResources(ArkString projectName) override;
	void SynchronizeResources(ArkString projectName) override;
	size_t ShaderFactory::size() const override { return m_loadedShaders.size(); }
	void clear() override;

	void compileShaders();

private:
	std::vector<ArkRendering::ShaderProgram *> m_loadedShaders;

	void createShaderFromString(ArkString string);

};