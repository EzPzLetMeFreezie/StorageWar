#include "container.h"

int AbstractContainer::m_containerCounter = 0;

AbstractContainer* AbstractContainer::CreateContainer(ContainerType type)
{
	AbstractContainer* container = nullptr;

	if (type == CT_NonRefrigerated)
	{
		return new NonRefrigeratedContainer(std::to_string(m_containerCounter++));
	}
	else if (type == CT_Refrigerated)
	{
		return new RefrigeratedContainer(std::to_string(m_containerCounter++));
	}

	return container;
}

ObjectID AbstractContainer::getStoredObjectID() const
{
	return m_isEmpty ? INVALID_OBJECT_ID : m_obj->getID();
}

ObjectTypeName AbstractContainer::getStoredObjectType() const
{
	return !m_isEmpty ? m_obj->toString() : ObjectTypeName();
}

StorableObject* const AbstractContainer::retrieveObject()
{
	StorableObject* storedObject = nullptr;
	if (!m_obj || m_obj->getID() == INVALID_OBJECT_ID)
	{
		return storedObject;
	}

	storedObject = m_obj;
	m_obj = nullptr;
	m_isEmpty = true;
	return storedObject;
}

RefrigeratedContainer::RefrigeratedContainer(ContainerID id)
	: AbstractContainer(id)
{
	m_isRefrigerated = true;
}

RefrigeratedContainer::~RefrigeratedContainer()
{
}

const ContainerType RefrigeratedContainer::getType() const
{
	return CT_Refrigerated;
}

NonRefrigeratedContainer::NonRefrigeratedContainer(ContainerID id)
	: AbstractContainer(id)
{
	m_isRefrigerated = false;
}

NonRefrigeratedContainer::~NonRefrigeratedContainer()
{
}

const ContainerType NonRefrigeratedContainer::getType() const
{
	return CT_NonRefrigerated;
}
