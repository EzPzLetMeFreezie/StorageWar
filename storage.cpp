#include <algorithm>

#include "Storage.h"

Storage::Storage()
{
}

Storage::~Storage()
{
	for (auto container : m_Containers) {
		delete container.second;
	}
	for (auto pod : m_Pods) {
		delete pod.second;
	}
}

Storage::Storage(Storage&& other)
{
	std::swap(m_Pods, other.m_Pods);
	std::swap(m_Containers, other.m_Containers);
	std::swap(m_EmptyContainers, other.m_EmptyContainers);
	std::swap(m_StoredObjects, other.m_StoredObjects);
}

Storage& Storage::operator=(Storage&& other)
{
	if (this != &other)
	{
		std::swap(m_Pods, other.m_Pods);
		std::swap(m_Containers, other.m_Containers);
		std::swap(m_EmptyContainers, other.m_EmptyContainers);
		std::swap(m_StoredObjects, other.m_StoredObjects);
	}

	return *this;
}

void Storage::addContainerPod(ContainerType type, int count)
{
	m_Pods[type] = new Pod(type, count);
}

const ContainerID Storage::addContainer(ContainerType type)
{
	if (m_Pods[type]->containers.size() >= m_Pods[type]->limit) return INVALID_CONTAINER_ID;
	ContainerBase* container = ContainerBase::CreateContainer(type);
	m_Pods[type]->containers.push_back(container);
	m_Containers[container->getId()] = container;
	m_EmptyContainers[type].push_back(container);
	return container->getId();
}

const bool Storage::removeContainer(ContainerID id)
{
	if (id == INVALID_CONTAINER_ID || m_Containers.find(id) == m_Containers.end()) return false;
	ContainerBase* container = m_Containers[id];
	m_Containers.erase(id);
	m_Pods[container->getType()]->containers.remove(container);
	m_EmptyContainers[container->getType()].remove(container);
	delete container;
	return true;
}

const ObjectID Storage::storeObject(StorableObject* object, ContainerType type)
{
	if (!object) return INVALID_OBJECT_ID;
	if (m_EmptyContainers[type].empty()) return INVALID_OBJECT_ID;
	ContainerBase* container = m_EmptyContainers[type].back();
	m_StoredObjects[container->storeObject(object)] = container->getId();
	m_EmptyContainers[type].pop_back();
	return object->getID();
}

const bool Storage::isObjectInStorage(ObjectID objectID) const
{
	if (objectID == INVALID_OBJECT_ID) return false;
	return m_StoredObjects.find(objectID) != m_StoredObjects.end();
}

StorableObject* const Storage::retrieveObject(ObjectID objectID)
{
	if (!isObjectInStorage(objectID)) return nullptr;
	ContainerBase* container = m_Containers[m_StoredObjects[objectID]];
	m_StoredObjects.erase(objectID);
	m_EmptyContainers[container->getType()].push_back(container);
	return container->retrieveObject();
}

void Storage::displayContainer() const
{
	std::printf("Display the content the storage\n");
	for (auto podIt = m_Pods.rbegin(); podIt != m_Pods.rend(); podIt++) {
		Pod* pod = podIt->second;
		if (podIt != m_Pods.rbegin()) {
			std::printf("\n");
		}
		std::printf("%s content:\n", pod->type.c_str());
		for (auto container : pod->containers) {
			if (container->getStoredObjectID() != INVALID_OBJECT_ID) {
				printf("ObjectID: %s \t\t %s\n", std::to_string(container->getStoredObjectID()).c_str(), container->getStoredObjectType().c_str());
			}
		}
	}
	std::printf("-----------\n");
}
