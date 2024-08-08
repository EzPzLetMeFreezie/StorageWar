#include "player.h"

#include "assert.h"

Player::~Player()
{
	delete m_Storage;
}

ObjectID Player::storeObject(StorableObject* object)
{
	assert(object);
	return m_Storage->storeObject(object);
}

void Player::displayStorage() const
{
	m_Storage->displayContainer();
}

Storage* Player::getStorage()
{
	return m_Storage;
}

void Player::allocateStorage(Storage* storage)
{
	m_Storage = storage;
}

const std::string Player::toString()
{
	return m_Name;
}

