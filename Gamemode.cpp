#include <assert.h>
#include <list>
#include <random>
#include <sstream>
#include <iostream>

#include "Gamemode.h"
#include "StorableObject.h"
#include "ContainerBase.h"

Gamemode::Gamemode()
{
	m_ObjectManager = new ObjectManager();
}

Gamemode::~Gamemode()
{
	for (auto player : m_Players)
	{
		delete player;
	}
	delete m_ObjectManager;
}

void Gamemode::setupPlayers(short playerCount)
{
	for (int i = 0; i < playerCount; ++i)
	{
		static char buffer[10];
		sprintf_s(buffer, "Player%0d", i);
		Player* player = new Player(buffer);
		player->allocateStorage(createStorage(m_NonRefridgerationContainerCount, m_RefridgerationContainerCount));

		generateInitialStorageState(*player->getStorage());

		m_Players.push_back(player);
	}
}

void Gamemode::startGame()
{
	Player* winningPlayer = nullptr;
	do
	{
		// Each players play in turn
		for (int playerIndex = 0; playerIndex < m_Players.size(); ++playerIndex)
		{
			if (winningPlayer = playerTakeTurn(playerIndex)) {
				break;
			}
		}
	} while (!winningPlayer);
	assert(winningPlayer);

	std::printf("%s won the game!\n", winningPlayer->toString().c_str());
}

Player* Gamemode::playerTakeTurn(int playerIndex)
{

	Player* currentPlayer = getPlayer(playerIndex);
	Player* opponentPlayer = getOpponentPlayer(playerIndex);
	std::printf("%s to play\n", currentPlayer->toString().c_str());

	// spawn random object
	StorableObject* object = m_ObjectManager->generateRandomObjectType();
	std::printf("%s spawned\n", object->toString().c_str());

	// player handle new object
	if (!handleStorage(currentPlayer, object))
	{
		return opponentPlayer;
	}

	// player send new object to opponent
	if (!handleStorage(opponentPlayer, pickObjectToSend(currentPlayer)))
	{
		return currentPlayer;
	}

	// player end of turn
	std::printf("\n-------------------------\nEnd of turn\n-------------------------\n");
	return nullptr;
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
		std::string idToRetrieve;
		printf("Enter a valid ObjectID: ");
		std::cin >> idToRetrieve;
		try {
			retrievedObject = player->getStorage()->retrieveObject(std::stoi(idToRetrieve));
		} catch (...) {
			retrievedObject = nullptr;
		}
		if (!retrievedObject) {
			std::printf("Invalid ObjectID %s. Please try again.\n", idToRetrieve.c_str());
		}
	} while (!retrievedObject);
	return retrievedObject;
}

Player* Gamemode::getPlayer(int playerIndex)
{
	return m_Players[playerIndex];
}

Player* Gamemode::getOpponentPlayer(int playerIndex)
{
	int opponentIndex = playerIndex + 1;
	if (opponentIndex >= m_Players.size())
	{
		opponentIndex = 0;
	}
	return getPlayer(opponentIndex);
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
	m_RefridgerationContainerCount = count;
}

void Gamemode::setNonRefridgerationContainerCount(short count)
{
	m_NonRefridgerationContainerCount = count;
}

void Gamemode::generateInitialStorageState(Storage& storage)
{
	// ????
}

