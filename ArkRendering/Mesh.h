#pragma once
#include <vector>

#include "Vec3.h"
#include "Vec2.h"

struct Mesh
{
	struct Vertex
	{
		Vec3 point;
		Vec3 normal;
		Vec2 uv;
	};

	std::vector<Vertex> m_vertices;

	Mesh();

};