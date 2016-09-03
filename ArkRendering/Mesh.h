#include <vector>

#include "Vec3.h"
#include "Vec2.h"

struct Mesh
{
public:
	Mesh();

private:
	std::vector<Vec3> mVertices;
	std::vector<Vec2> mUvs;
	//std::vector<Vec3> tris;	// TODO Mesh::tris implement triangles?
};