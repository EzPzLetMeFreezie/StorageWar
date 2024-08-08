#pragma once

#include "FoodObject.h"
#include "IRefridgable.h"

struct RegrigaratedFoodObject : public FoodObject, virtual IRefridgable
{
public:
	RegrigaratedFoodObject(ObjectID objectID) : FoodObject(objectID) {}

	const ObjectTypeName toString() const { return ObjectTypes[(int)EObjectType::RefrigeratedFood]; }
	const EObjectType getType() const { return EObjectType::RefrigeratedFood; }
	virtual const bool isRefrigerated() const override { return true; }
};
