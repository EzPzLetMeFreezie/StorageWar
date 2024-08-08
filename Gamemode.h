#include <vector>
#include "Player.h"
#include "ObjectManager.h"

#pragma once

class Gamemode
{
public:
	Gamemode();
	~Gamemode();

private:
	std::vector<Player*> m_players;
	ObjectManager* m_objectManager;
	short m_refridgerationContainerCount = 8;
	short m_nonRefridgerationContainerCount = 16;

	void generateInitialStorageState(Storage& storage);
	Player* playerTakeTurn(int playerIndex);
	bool handleStorage(Player* player, StorableObject* object);
	StorableObject* pickObjectToSend(Player* player);
	class Storage* createStorage(const short& nonRefrigeratedContainerCount, const short& refrigeratedContainerCount);

public:
	void setupPlayers(short playerCount);
	int startGame();
	void setRefridgerationContainerCount(short count);
	void setNonRefridgerationContainerCount(short count);
};