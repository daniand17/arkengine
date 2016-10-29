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