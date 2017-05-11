#pragma once

#include "ProjectResource.h"
#include <vector>
#include "Vec3.h"
#include "Vec2.h"

struct Vertex
{
	Vec3 point;
	Vec3 normal;
	Vec2 uv;
};



class MeshResource : public ProjectResource
{
public:
	MeshResource(ArkString name, ArkString filepath);

	// Inherited via ProjectResource
	virtual void serialize() const override;
	virtual void deserialize() override;


private:
	std::vector<Vertex> m_vertices;

	bool loadOBJ(ArkString path, std::vector<Vec3>& outVertices, std::vector<Vec2>& outUVs, std::vector<Vec3>& outNormals);
};