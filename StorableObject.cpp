#include "StorableObject.h"
#include "FurnitureObject.h"
#include "ElectronicObject.h"
#include "FoodObject.h"
#include "RegrigaratedFoodObject.h"
#include "MedicineObject.h"
#include "RefrigeratedMedicineObject.h"

StorableObject* const StorableObject::CreateObject(EObjectType objectType, ObjectID objectID)
{
	switch (objectType)
	{
	case EObjectType::Furniture:
		return new FurnitureObject(objectID);
		break;
	case EObjectType::Electronic:
		return new ElectronicObject(objectID);
		break;
	case EObjectType::Food:
		return new FoodObject(objectID);
		break;
	case EObjectType::RefrigeratedFood:
		return new RegrigaratedFoodObject(objectID);
		break;
	case EObjectType::Medicine:
		return new MedicineObject(objectID);
		break;
	case EObjectType::RefrigeratedMedicine:
		return new RefrigeratedMedicineObject(objectID);
		break;
	case EObjectType::MAX:
		break;
	case EObjectType::INVALID:
		break;
	default:
		break;
	}
}

