#pragma once

#include "StorableObject.h"

struct MedicineObject : public StorableObject
{
public:
	MedicineObject(ObjectID objectID) : StorableObject(objectID) {}

	const ObjectTypeName toString() const { return ObjectTypes[(int)EObjectType::Medicine]; }
	const EObjectType getType() const { return EObjectType::Medicine; }
};
