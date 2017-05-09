#pragma once
#include "Vec3.h"
#include "Quaternion.h"
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	Vec3 getPosition() const { return m_position; }
	Quaternion getRotation() const { return m_rotation; }

	void setPosition(Vec3 position) { m_position = position; }
	void setRotation(Quaternion rotation) { m_rotation = rotation; }

	ArkString toString() const { return ArkString("(Transform) ") + m_position.toString(); }

	// Inherited via Component
	virtual ArkString serialize() const override;
	virtual void deserialize(ArkString) override;
	void copyFrom(Component const * component) override;

private:
	Vec3 m_position;
	Quaternion m_rotation;
};