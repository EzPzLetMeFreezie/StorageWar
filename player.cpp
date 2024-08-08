#include "player.h"

#include "assert.h"

ObjectID Player::storeObject(StorableObject* object)
{
	assert(object);
	return m_Storage.storeObject(object);
}

StorableObject* const Player::retrieveObject(ObjectID objectID)
{
	if (objectID == INVALID_OBJECT_ID)
	{
		return nullptr;
	}

	return m_Storage.retrieveObject(objectID);
}

void Player::displayStorage() const
{
	m_Storage.displayContainer();
}
