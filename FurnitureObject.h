#pragma once

#include "StorableObject.h"

struct FurnitureObject : public StorableObject
{
public:
	FurnitureObject(ObjectID objectID) : StorableObject(objectID) {}

	const ObjectTypeName toString() const { return ObjectTypes[(int)EObjectType::Furniture]; }
	const EObjectType getType() const { return EObjectType::Furniture; }
};
