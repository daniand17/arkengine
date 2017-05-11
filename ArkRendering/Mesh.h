#pragma once
#include <vector>
#include "ArkString.h"
#include "MeshResource.h"


struct Mesh
{
	ArkString name;
	

	std::vector<Vertex> m_vertices;

	Mesh();

};