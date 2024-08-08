#include <vector>
#include "player.h"
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


	Storage createStorage(const short& nonRefrigeratedContainerCount, const short& refrigeratedContainerCount);
	void generateInitialStorageState(Storage& storage);

public:
	void setupPlayers(short playerCount);
	int startGame();
	void setRefridgerationContainerCount(short count);
	void setNonRefridgerationContainerCount(short count);
};