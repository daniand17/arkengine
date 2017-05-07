#pragma once
#include "Resource.h"
#include "Vec3.h"
#include "ShaderProgram.h"
#include "RenderPass.h"


struct MaterialInfo : Resource
{
	MaterialInfo();

	void createRenderPass(ArkString name, ArkString vertexShader, ArkString fragmentShader);
	std::vector<RenderPass *> getRenderPasses() const { return m_renderPasses; }

private:
	bool m_bound;
	std::vector<RenderPass *> m_renderPasses;
};