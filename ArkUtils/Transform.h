#include <vector>

#include "Vec3.h"

struct Transform
{
private:
	Vec3 position;
	std::vector<Transform *> children;
};