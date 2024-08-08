#pragma once

#include "MedicineObject.h"
#include "IRefridgable.h"

struct RefrigeratedMedicineObject : public MedicineObject, virtual IRefridgable
{
public:
	RefrigeratedMedicineObject(ObjectID objectID) : MedicineObject(objectID) {}
	
	const ObjectTypeName toString() const { return ObjectTypes[(int)EObjectType::RefrigeratedMedicine]; }
	const EObjectType getType() const { return EObjectType::RefrigeratedMedicine; }
	virtual const bool isRefrigerated() const override { return true; }
};
