#pragma once

#include "storage.h"
#include "StorableObject.h"

#include <string>

struct Player
{
public:
	Player(const char* name) : m_Name(name) {}
	~Player();
private:
	const std::string m_Name;
	Storage* m_Storage;
public:
	// Store an object
	ObjectID storeObject(StorableObject* object);
	// Diplay the contain of the player storage.
	void displayStorage() const;
	Storage* getStorage();
	void allocateStorage(Storage* storage);
	const std::string toString();
};
