#pragma once

#include <string>
#include "StorableObject.h"

using ContainerType = std::string;
using ContainerID = std::string;
static const ContainerID INVALID_CONTAINER_ID = "INVALID_OBJECT_ID";

enum class EContainerType : char
{
	Refrigerated,
	NonRefrigerated,
	MAX
};

static std::string ContainerTypes[(char)(EContainerType::MAX)] = {
	"Refrigerated",
	"NonRefrigerated"
};

#define CT(t)				ContainerTypes[(char)t]
#define CT_NonRefrigerated	CT(EContainerType::NonRefrigerated)
#define CT_Refrigerated		CT(EContainerType::Refrigerated)

class ContainerBase
{
public:
	ContainerBase(ContainerID id) : m_ID(id), m_IsEmpty(true), m_IsRefrigerated(false) {
		m_Obj = nullptr;
	}
	virtual ~ContainerBase() = 0 {};

	// Return true if refrigerated.
	const bool isRefrigerated() const { return m_IsRefrigerated; }
	// Return true if empty.
	const bool isEmpty() const { return m_IsEmpty; }
	// Return the type of the container
	virtual const ContainerType getType() const = 0;

	// Store an object.
	template< typename Object >
	const ObjectID storeObject(Object* object)
	{
		m_IsEmpty = false;
		m_Obj = object;
		return m_Obj->getID();
	}

	// Return the object ID	
	ObjectID getStoredObjectID() const;
	// Return the object type
	ObjectTypeName getStoredObjectType() const;
	// Retrieve an object.
	StorableObject* const retrieveObject();

	// Return an ID
	ContainerID getId() const { return m_ID; }

	// Create a container.
	static ContainerBase* CreateContainer(ContainerType type);

protected:
	ContainerID m_ID;
	bool m_IsRefrigerated;
	bool m_IsEmpty;
	StorableObject* m_Obj;
private:
	static int m_ContainerCounter;
};