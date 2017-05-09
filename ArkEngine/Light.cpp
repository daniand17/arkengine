#include "Light.h"

Light::Light()
	: Component(CI_Light)
{
}



ArkString Light::serialize() const
{
	// TODO (AD) Light serialize stub
	return ArkString("Light::serialize()");
}



void Light::deserialize(ArkString)
{
	// TODO (AD) Light deserialize stub
}



ArkString Light::toString() const
{
	return ArkString();
}



void Light::copyFrom(Component const * component)
{
}