#pragma once
#include "Component.h"
#include "ArkRendering.h"
#include "Mesh.h"

class Renderer : public Component
{
public:
	Renderer(GameObject * obj);

	MaterialInfo * getMaterial() const { return m_material; }
	bool receivesShadows() const { return m_doShadows; }

	void setMaterial(MaterialInfo * material) { m_material = material; }

	virtual ArkString toString() const override { return ArkString("Renderer"); }

protected:
	MaterialInfo * m_material;
	bool m_doShadows;
};


class MeshRenderer : public Renderer
{
public:
	MeshRenderer(GameObject * gameObject);

	Mesh * getMesh() const { return m_mesh; }
	void setMesh(Mesh * mesh) { m_mesh = mesh; }

	ArkString toString() const override { return ArkString("MeshRenderer"); }

	void copyFrom(Component const * component) override;
	ArkString getJson() const override;

private:
	Mesh * m_mesh;
};