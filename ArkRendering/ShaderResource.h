#pragma once
#include "ProjectResource.h"


class ShaderResource : public ProjectResource
{
public:
	ShaderResource(ArkString name, ArkString filepath);

	// Inherited via ProjectResource
	virtual void serialize() const override;
	virtual void deserialize() override;
	ArkString const & getSource() const { return m_shaderSource; }
private:

	ArkString m_shaderSource;
};