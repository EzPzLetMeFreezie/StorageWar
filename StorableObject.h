#pragma once

#include "ObjectBase.h"

class StorableObject : public ObjectBase
{
public:
	StorableObject(ObjectID objectID) : ObjectBase(objectID) {}

	virtual const bool isRefrigerated() const { return false; }
	static StorableObject* const CreateObject(EObjectType objectType, ObjectID objectID);
};