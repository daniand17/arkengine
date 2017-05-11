#pragma once

#include "MaterialResource.h"
#include "Mat4.h"
#include "Mesh.h"

struct RendererInfo
{
	enum RendererType
	{
		RT_Mesh,
		RT_NumTypes
	};

	RendererInfo(RendererType type, MaterialResource * material, Mat4 const & modelMatrix, Mesh * mesh)
		: m_type(type)
		, m_material(material)
		, m_modelMatrix(modelMatrix)
		, m_mesh(mesh)
	{
	}

	MaterialResource * m_material;
	Mesh * m_mesh;
	Mat4 m_modelMatrix;
	RendererType m_type;
};