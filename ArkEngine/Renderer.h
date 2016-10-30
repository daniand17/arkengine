#pragma once
#include "Component.h"
#include "ArkRendering.h"

class Renderer : public Component
{
public:
	Renderer(GameObject * obj);

	ArkRendering::MaterialInfo * getMaterial() const { return m_material; }
	bool receivesShadows() const { return m_doShadows; }

	void setMaterial(ArkRendering::MaterialInfo * material) { m_material = material; }

	virtual ArkString toString() const override { return ArkString("Renderer"); }

protected:
	ArkRendering::MaterialInfo * m_material;
	bool m_doShadows;
};


class MeshRenderer : public Renderer
{
public:
	MeshRenderer(GameObject * gameObject);

	ArkRendering::MeshInfo * getMesh() const { return m_mesh; }
	void setMesh(ArkRendering::MeshInfo * mesh) { m_mesh = mesh; }

	ArkString toString() const override { return ArkString("MeshRenderer"); }

	void copyFrom(Component const * component) override;

private:
	ArkRendering::MeshInfo * m_mesh;
};