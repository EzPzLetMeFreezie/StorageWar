#include <assert.h>
#include <list>
#include <random>
#include <stdio.h>
#include <iostream>

#include "Gamemode.h"
#include "StorableObject.h"
#include "ContainerBase.h"

Gamemode::Gamemode()
{
	m_objectManager = new ObjectManager();
}

Gamemode::~Gamemode()
{
	for (auto player : m_players)
	{
		delete player;
	}
	delete m_objectManager;
}

void Gamemode::setupPlayers(short playerCount)
{
	for (int i = 0; i < playerCount; ++i)
	{
		static char buffer[10];
		sprintf_s(buffer, "Player%0d", i);
		Player* player = new Player(buffer);
		player->allocateStorage(createStorage(m_nonRefridgerationContainerCount, m_refridgerationContainerCount));

		generateInitialStorageState(*player->getStorage());

		m_players.push_back(player);
	}
}

int Gamemode::startGame()
{
	bool isGameRunning = true;
	int playerIndex = 0;
	int winningPlayerIndex = 0xFFFFFFFF;
	do
	{
		// Each players play in turn
		for (playerIndex = 0; playerIndex < m_players.size(); ++playerIndex)
		{
			if (!playerTakeTurn(playerIndex, winningPlayerIndex)) {
				isGameRunning = false;
				break;
			}
		}
	} while (isGameRunning);
	assert(winningPlayerIndex != 0xFFFFFFFF);

	std::printf("%s won the game!\n", m_players[winningPlayerIndex]->toString().c_str());
	return 0;
}

bool Gamemode::playerTakeTurn(int playerIndex, int& winningPlayerIndex)
{
	// find opponent player index
	int opponentIndex = playerIndex + 1;
	if (opponentIndex >= m_players.size())
	{
		opponentIndex = 0;
	}

	Player* currentPlayer = m_players[playerIndex];
	std::printf("%s to play\n", currentPlayer->toString().c_str());

	// spawn random object
	StorableObject* object = m_objectManager->generateRandomObjectType();
	std::printf("%s spawned\n", object->toString().c_str());

	// player handle new object
	if (!handleStorage(currentPlayer, object))
	{
		winningPlayerIndex = opponentIndex;
		return false;
	}

	// player send new object to opponent
	Player* opponent = m_players[opponentIndex];
	if (!handleStorage(opponent, pickObjectToSend(currentPlayer)))
	{
		winningPlayerIndex = playerIndex;
		return false;
	}

	// player end of turn
	std::printf("\n-------------------------\nEnd of turn\n-------------------------\n");
	return true;
}

bool Gamemode::handleStorage(Player* player, StorableObject* object)
{
	ObjectID objecID = player->storeObject(object);
	if (objecID == INVALID_OBJECT_ID)
	{
		std::printf("%s was not able to store %s\n", player->toString().c_str(), object->toString().c_str());
		return false;
	}
	else
	{
		std::printf("%s successfully stored the object.\n", player->toString().c_str());
		return true;
	}
}

StorableObject* Gamemode::pickObjectToSend(Player* player)
{
	std::printf("%s: Pick an object by ObjectID to send to your opponent\n", player->toString().c_str());
	StorableObject* retrievedObject = nullptr;
	do {
		player->displayStorage();
		ObjectID idToRetrieve;
		printf("Enter a valid ObjectID: ");
		std::cin >> idToRetrieve;
		retrievedObject = player->getStorage()->retrieveObject(idToRetrieve);
		if (!retrievedObject) {
			std::printf("Invalid ObjectID %s. Please try again.\n", std::to_string(idToRetrieve).c_str());
		}
	} while (!retrievedObject);
	return retrievedObject;
}

Storage* Gamemode::createStorage(const short& nonRefrigeratedContainerCount, const short& refrigeratedContainerCount)
{
	Storage* storage = new Storage();

	storage->addContainerPod(CT_Refrigerated, refrigeratedContainerCount);
	for (int i = 0; i < refrigeratedContainerCount; i++)
	{
		storage->addContainer(CT_Refrigerated);
	}
	storage->addContainerPod(CT_NonRefrigerated, nonRefrigeratedContainerCount);

	for (int i = 0; i < nonRefrigeratedContainerCount; i++)
	{
		storage->addContainer(CT_NonRefrigerated);
	}

	return storage;
}

void Gamemode::setRefridgerationContainerCount(short count)
{
	m_refridgerationContainerCount = count;
}

void Gamemode::setNonRefridgerationContainerCount(short count)
{
	m_nonRefridgerationContainerCount = count;
}

void Gamemode::generateInitialStorageState(Storage& storage)
{
	// ????
}

