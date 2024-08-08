#include "ContainerBase.h"
#include "RefrigeratedContainer.h"
#include "NonRefrigeratedContainer.h"

int ContainerBase::m_containerCounter = 0;

ContainerBase* ContainerBase::CreateContainer(ContainerType type)
{
	ContainerBase* container = nullptr;

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

ObjectID ContainerBase::getStoredObjectID() const
{
	return m_isEmpty ? INVALID_OBJECT_ID : m_obj->getID();
}

ObjectTypeName ContainerBase::getStoredObjectType() const
{
	return !m_isEmpty ? m_obj->toString() : ObjectTypeName();
}

StorableObject* const ContainerBase::retrieveObject()
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
