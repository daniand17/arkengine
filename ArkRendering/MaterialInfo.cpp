#include "MaterialInfo.h"

MaterialInfo::MaterialInfo()
{
}



void MaterialInfo::createRenderPass(ArkString name, ArkString vertexShader, ArkString fragmentShader)
{
	m_renderPasses.push_back(new RenderPass(name, vertexShader, fragmentShader));
}
