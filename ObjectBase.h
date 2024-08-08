#pragma once

#include <string>

#pragma warning( disable : 4250 )

using ObjectID = int;
using ObjectTypeName = std::string;
static const ObjectID INVALID_OBJECT_ID = -1;
static const ObjectTypeName INVALID_OBJECT_NAME = "INVALID_OBJECT_ID";

enum class EObjectType : char
{
	Furniture,
	Electronic,
	Food,
	RefrigeratedFood,
	Medicine,
	RefrigeratedMedicine,
	MAX,
	INVALID
};

static std::string ObjectTypes[(char)(EObjectType::MAX)] = {
	"Furniture",
	"Electronic",
	"Food",
	"RefrigeratedFood",
	"Medicine",
	"RefrigeratedMedicine",
};

class ObjectBase
{
public:
	ObjectBase(ObjectID objectID) { m_ObjectID = objectID; }
	virtual ~ObjectBase() { m_ObjectID = INVALID_OBJECT_ID; }

	virtual const EObjectType getType() const = 0 { return EObjectType::INVALID; }
	virtual const ObjectTypeName toString() const = 0 { return INVALID_OBJECT_NAME; }
	virtual const ObjectID getID() const { return m_ObjectID; };

protected:
	ObjectID m_ObjectID;

private:
	static int m_Count;
};
