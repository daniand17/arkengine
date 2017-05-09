#pragma once
#include "Component.h"

class Light : public Component
{

public:
	Light();
	// Inherited via Component
	virtual ArkString serialize() const override;
	virtual void deserialize(ArkString) override;
	virtual ArkString toString() const override;
	virtual void copyFrom(Component const * component) override;
};