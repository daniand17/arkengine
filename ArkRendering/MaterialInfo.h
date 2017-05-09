#pragma once
#include "Resource.h"
#include "Vec3.h"
#include "ShaderProgram.h"
#include "RenderPass.h"
#include <list>

struct MaterialInfo : Resource
{
	MaterialInfo();

	void createRenderPass(ArkString name, ArkString vertexShader, ArkString fragmentShader);
	std::list<RenderPass *> getRenderPasses() const { return m_renderPasses; }

private:
	bool m_bound;
	std::list<RenderPass *> m_renderPasses;
};