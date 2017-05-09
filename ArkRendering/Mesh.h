#pragma once
#include <vector>
#include "ArkString.h"
#include "Vec3.h"
#include "Vec2.h"

struct Mesh
{
	ArkString name;
	struct Vertex
	{
		Vec3 point;
		Vec3 normal;
		Vec2 uv;
	};

	std::vector<Vertex> m_vertices;

	Mesh();

};