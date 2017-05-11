#pragma once
#include "ArkString.h"
#include "YAML_Util.h"

class I_Serializable
{
public:
	enum ClassIDs
	{
		CI_GameObject,
		CI_Rigidbody,
		CI_Light,
		CI_MeshRenderer,
		CI_Transform
	};

	I_Serializable(ClassIDs id) : m_classID(id) {}


	virtual ArkString serialize() const = 0;
	virtual void deserialize(ArkString) = 0;
	unsigned getClassId() const { return static_cast<unsigned>(m_classID); }
protected:

	ClassIDs m_classID;
};

////////////////////////////////////

struct SerializableRelationship
{
	SerializableRelationship(unsigned id, unsigned parentId, I_Serializable * item)
		: parentId(parentId)
		, fileId(id)
		, serializableItem(item)
	{
	}
	I_Serializable * serializableItem;

	unsigned parentId;
	unsigned fileId;
};