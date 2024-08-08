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
		player->m_Storage = createStorage(m_nonRefridgerationContainerCount, m_refridgerationContainerCount);

		generateInitialStorageState(player->m_Storage);

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

	std::printf("%s won the game!\n", m_players[winningPlayerIndex]->m_Name.c_str());
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

	Player* p = m_players[playerIndex];
	std::printf("%s to play\n", p->m_Name.c_str());

	// spawn random object
	StorableObject* object = m_objectManager->generateRandomObjectType();
	std::printf("%s spawned\n", object->toString().c_str());

	// player handle new object
	{
		ObjectID objecID = p->storeObject(object);
		if (objecID == INVALID_OBJECT_ID)
		{
			std::printf("%s was not able to store %s\n", p->m_Name.c_str(), object->toString().c_str());
			winningPlayerIndex = opponentIndex;
			return false;
		}
		else
		{
			std::printf("%s successfully stored the object.\n", p->m_Name.c_str());
		}
	}

	// player pick object
	StorableObject* objetToSend = nullptr;
	std::printf("%s: Pick an object by ObjectID to send to your opponent\n", p->m_Name.c_str());
	do {
		p->displayStorage();
		ObjectID idToRetrieve;
		printf("Enter a valid ObjectID: ");
		std::cin >> idToRetrieve;
		StorableObject* const retrievedObject = p->retrieveObject(idToRetrieve);
		if (!retrievedObject) {
			std::printf("Invalid ObjectID %s. Please try again.\n", std::to_string(idToRetrieve).c_str());
		}
		else
		{
			objetToSend = retrievedObject;
		}
	} while (!objetToSend);

	// player send new object to opponent
	Player* opponent = m_players[opponentIndex];
	{
		ObjectID objecID = opponent->storeObject(objetToSend);
		if (objecID == INVALID_OBJECT_ID)
		{
			std::printf("%s was not able to store %s\n", opponent->m_Name.c_str(), objetToSend->toString().c_str());
			winningPlayerIndex = playerIndex;
			return false;
		}
		else
		{
			std::printf("%s successfully stored the object.\n", opponent->m_Name.c_str());
		}
	}
	// player end of turn
	std::printf("\n-------------------------\nEnd of turn\n-------------------------\n");
	return true;
}

void Gamemode::setRefridgerationContainerCount(short count)
{
	m_refridgerationContainerCount = count;
}

void Gamemode::setNonRefridgerationContainerCount(short count)
{
	m_nonRefridgerationContainerCount = count;
}

Storage Gamemode::createStorage(const short& nonRefrigeratedContainerCount, const short& refrigeratedContainerCount)
{
	Storage s;

	s.setMaxContainerCount(CT_NonRefrigerated, nonRefrigeratedContainerCount);

	for (int i = 0; i < nonRefrigeratedContainerCount; i++)
	{
		s.addContainer(CT_NonRefrigerated);
	}

	s.setMaxContainerCount(CT_Refrigerated, refrigeratedContainerCount);

	for (int i = 0; i < refrigeratedContainerCount; i++)
	{
		s.addContainer(CT_Refrigerated);
	}

	return s;
}

void Gamemode::generateInitialStorageState(Storage& storage)
{
	// ????
}

