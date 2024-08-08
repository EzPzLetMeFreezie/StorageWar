#include "player.h"

#include "assert.h"

Player::~Player()
{
	delete m_Storage;
}

ObjectID Player::storeObject(StorableObject* object)
{
	assert(object);
	EContainerType containerType = (object->isRefrigerated()) ? EContainerType::Refrigerated : EContainerType::NonRefrigerated;
	return m_Storage->storeObject(object, ContainerTypes[(char)containerType]);
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

