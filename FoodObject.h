#pragma once

#include "StorableObject.h"

struct FoodObject : public StorableObject
{
public:
	FoodObject(ObjectID objectID) : StorableObject(objectID) {}
	
	const ObjectTypeName toString() const { return ObjectTypes[(int)EObjectType::Food]; }
	const EObjectType getType() const { return EObjectType::Food; }
};
