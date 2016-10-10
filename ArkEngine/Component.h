
#include "Transform.h"

class Component
{
public:
	Transform const * getTransform() { return mTransform; }

private:
	Transform * mTransform;
};