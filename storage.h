#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "StorableObject.h"
#include "ContainerBase.h"

#pragma once

struct Pod {
	int limit;
	ContainerType type;
	std::list<ContainerBase*> containers;

	Pod(ContainerType type, int count) : type(type), limit(count) {}
};

class Storage
{
public:
	Storage();
	virtual ~Storage() final;
	Storage(const Storage& other) = delete;
	Storage& operator=(const Storage& other) = delete;
	Storage(Storage&& other);
	Storage& operator=(Storage&& other);

private:
	std::map<ContainerID, ContainerBase*> m_Containers;
	std::map<ContainerType, Pod*> m_Pods;
	std::map<ContainerType, std::list<ContainerBase*>> m_EmptyContainers;
	std::map<ObjectID, ContainerID> m_StoredObjects;

public:
	// Set the maximum container count.
	void addContainerPod(ContainerType type, int count);
	// add a container
	const ContainerID addContainer(ContainerType type);
	// remove a container
	const bool removeContainer(ContainerID id);
	// Displayer the contain on the storage.
	void displayContainer() const;

	// Store an object of a given type.
	const ObjectID storeObject(StorableObject* object, ContainerType type);

	// Return true if the object is in storage
	const bool isObjectInStorage(ObjectID objectID) const;
	// retrieve an object.
	StorableObject* const retrieveObject(ObjectID objectID);
};
