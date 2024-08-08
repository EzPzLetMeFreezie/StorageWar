#include <assert.h>
#include <random>

#include "ObjectManager.h"
#include "StorableObject.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
}

StorableObject* ObjectManager::generateRandomObjectType()
{
	// Seed with a real random value, if available
	std::random_device device;

	// Choose a random mean between 1 and 6
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> uniformDist(0, static_cast<int>(EObjectType::MAX) - 1);

	const int randomNumber = uniformDist(engine);

	StorableObject* randomObject = nullptr;
	switch (randomNumber)
	{
	case 0:
		randomObject = StorableObject::CreateObject(EObjectType::Furniture, m_id_count++);
		break;
	case 1:
		randomObject = StorableObject::CreateObject(EObjectType::Electronic, m_id_count++);
		break;
	case 2:
		randomObject = StorableObject::CreateObject(EObjectType::Food, m_id_count++);
		break;
	case 3:
		randomObject = StorableObject::CreateObject(EObjectType::RefrigeratedFood, m_id_count++);
		break;
	case 4:
		randomObject = StorableObject::CreateObject(EObjectType::Medicine, m_id_count++);
		break;
	case 5:
		randomObject = StorableObject::CreateObject(EObjectType::RefrigeratedMedicine, m_id_count++);
		break;
	default:
		assert(false);
		break;
	}

	//std::printf(randomObject->isRefrigerated() ? "Refridged\n" : "not Refrided\n");
	assert(randomObject);
	return randomObject;
}
