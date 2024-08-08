#include <vector>

#pragma once

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
private:
	int m_id_count = 0;
	std::vector<class StorableObject*> m_objects;
public:
	class StorableObject* generateRandomObjectType();
};
