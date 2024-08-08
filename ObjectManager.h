#include <vector>

#pragma once

using namespace std;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
private:
	int m_id_count = 0;
	vector<class StorableObject*> m_objects;
public:
	class StorableObject* generateRandomObjectType();
};
