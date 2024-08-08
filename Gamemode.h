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
	std::vector<Player*> m_Players;
	ObjectManager* m_ObjectManager;
	short m_RefridgerationContainerCount = 8;
	short m_NonRefridgerationContainerCount = 16;

	void generateInitialStorageState(Storage& storage);
	Player* playerTakeTurn(int playerIndex);
	bool handleStorage(Player* player, StorableObject* object);
	StorableObject* pickObjectToSend(Player* player);
	class Storage* createStorage(const short& nonRefrigeratedContainerCount, const short& refrigeratedContainerCount);

public:
	void setupPlayers(short playerCount);
	void startGame();
	void setRefridgerationContainerCount(short count);
	void setNonRefridgerationContainerCount(short count);
	Player* getPlayer(int playerIndex);
	Player* getOpponentPlayer(int playerIndex);
};