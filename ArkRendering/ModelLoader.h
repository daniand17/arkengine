#include "ArkString.h"
#include <vector>
#include "Vec3.h"
#include "Vec2.h"

namespace ModelLoading
{
	bool loadOBJ(
		ArkString path,
		std::vector<Vec3> & outVertices,
		std::vector<Vec2> & outUVs,
		std::vector<Vec3> & outNormals);
}