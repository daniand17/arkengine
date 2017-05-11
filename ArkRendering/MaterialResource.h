#pragma once
#include "ProjectResource.h"
#include "Vec3.h"
#include "ShaderProgram.h"
#include "RenderPass.h"
#include <list>
#include "ShaderResource.h"

struct MaterialResource : public ProjectResource
{
	MaterialResource(ArkString name, ArkString filename);

	void createRenderPass(ShaderResource const * vertexShader, ShaderResource const * fragmentShader);
	std::list<RenderPass *> getRenderPasses() const { return m_renderPasses; }

	// Inherited via ProjectResource
	virtual void serialize() const override;
	virtual void deserialize() override;

	void genRenderPassInfo(ArkStringList &renderPasses);

private:
	bool m_bound;
	std::list<RenderPass *> m_renderPasses;
};