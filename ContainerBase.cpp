#include "ContainerBase.h"
#include "RefrigeratedContainer.h"
#include "NonRefrigeratedContainer.h"

int ContainerBase::m_ContainerCounter = 0;

ContainerBase* ContainerBase::CreateContainer(ContainerType type)
{
	ContainerBase* container = nullptr;

	if (type == CT_NonRefrigerated)
	{
		return new NonRefrigeratedContainer(std::to_string(m_ContainerCounter++));
	}
	else if (type == CT_Refrigerated)
	{
		return new RefrigeratedContainer(std::to_string(m_ContainerCounter++));
	}

	return container;
}

ObjectID ContainerBase::getStoredObjectID() const
{
	return m_IsEmpty ? INVALID_OBJECT_ID : m_Obj->getID();
}

ObjectTypeName ContainerBase::getStoredObjectType() const
{
	return !m_IsEmpty ? m_Obj->toString() : ObjectTypeName();
}

StorableObject* const ContainerBase::retrieveObject()
{
	StorableObject* storedObject = nullptr;
	if (!m_Obj || m_Obj->getID() == INVALID_OBJECT_ID)
	{
		return storedObject;
	}

	storedObject = m_Obj;
	m_Obj = nullptr;
	m_IsEmpty = true;
	return storedObject;
}
