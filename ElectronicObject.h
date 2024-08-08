#pragma once

#include "StorableObject.h"

struct ElectronicObject : public StorableObject
{
public:
	ElectronicObject(ObjectID objectID) : StorableObject(objectID) {}
	
	const ObjectTypeName toString() const { return ObjectTypes[(int)EObjectType::Electronic]; }
	const EObjectType getType() const { return EObjectType::Electronic; }
};
