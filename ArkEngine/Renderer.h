#pragma once
#include "Component.h"
#include "ArkRendering.h"
#include "Mesh.h"

class Renderer : public Component
{
public:
	Renderer(ClassIDs id);

	MaterialResource * getMaterial() const { return m_material; }
	bool receivesShadows() const { return m_doShadows; }

	void setMaterial(MaterialResource * material) { m_material = material; }

	virtual ArkString toString() const override { return ArkString("Renderer"); }

protected:
	MaterialResource * m_material;
	bool m_doShadows;
	virtual void copyFrom(Component const * component) override;

	virtual ArkString serialize() const override = 0;
	virtual void deserialize(ArkString) override = 0;
};


class MeshRenderer : public Renderer
{
public:
	MeshRenderer();
	Mesh * getMesh() const { return m_mesh; }
	void setMesh(Mesh * mesh) { m_mesh = mesh; }

	ArkString toString() const override { return ArkString("MeshRenderer"); }

	void copyFrom(Component const * component) override;

private:
	Mesh * m_mesh;

	// Inherited via Renderer
	virtual ArkString serialize() const override;
	virtual void deserialize(ArkString) override;
};