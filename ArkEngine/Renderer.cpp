#include "Renderer.h"

MeshRenderer::MeshRenderer(GameObject * gameObject)
	: Renderer(gameObject)
	, m_mesh(NULL)
{
}

Renderer::Renderer(GameObject * obj)
	: Component(obj)
	, m_doShadows(true)
	, m_material(NULL)
{
}

void MeshRenderer::copyFrom(Component const * component)
{
	MeshRenderer const * other = dynamic_cast<MeshRenderer const *>(component);
	m_mesh = other->m_mesh;
	m_material = other->m_material;
	m_doShadows = other->m_doShadows;
}
