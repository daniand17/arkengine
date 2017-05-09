#pragma once

#include "ISerializable.h"
#include "ArkString.h"
#include "Mat4.h"

class Transform;
struct Mat4;

class Component : public I_Serializable
{
public:
	Component(I_Serializable::ClassIDs id) : I_Serializable(id) {}

	virtual ArkString toString() const = 0;
	virtual void copyFrom(Component const * component) = 0;

	Mat4 getModelMatrix() const;

protected:
	Transform * m_transform;
};