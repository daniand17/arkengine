#include "Renderer.h"
#include "GameObject.h"

MeshRenderer::MeshRenderer()
	: Renderer(CI_MeshRenderer)
	, m_mesh(NULL)
{
}



Renderer::Renderer(ClassIDs id)
	: Component(id)
	, m_doShadows(true)
	, m_material(NULL)
{
}



void Renderer::copyFrom(Component const * component)
{
}



void MeshRenderer::copyFrom(Component const * component)
{
	MeshRenderer const * other = dynamic_cast<MeshRenderer const *>(component);
	m_mesh = other->m_mesh;
	m_material = other->m_material;
	m_doShadows = other->m_doShadows;
}



ArkString MeshRenderer::serialize() const
{
	ArkString str(YAML_Generator::genObjectNameHeader("MeshRenderer"));
	str += YAML_Generator::genBoolProperty("m_doShadows", m_doShadows);

	if ( m_mesh )
	{
		str += YAML_Generator::genStringProperty("m_meshName", m_mesh->name);
	}

	if ( m_material )
	{
		str += YAML_Generator::genStringProperty("m_material", m_material->getName());
	}

	return str;
}



void MeshRenderer::deserialize(ArkString str)
{
	// TODO (AD) Mesh Renderer deserialize stub
}
