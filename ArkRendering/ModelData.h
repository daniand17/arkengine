#pragma once

#include "ProjectResource.h"
#include "ArkString.h"
#include "Mat4.h"

#include "MaterialResource.h"
#include "Mesh.h"

struct ModelData
{
public:
	ModelData()
		: m_material(NULL)
		, m_mesh(NULL)
		, modelMatrix(Mat4::identity())
	{
	}

	MaterialResource * m_material;
	Mesh * m_mesh;
	Mat4 modelMatrix;
};