#include <assert.h>
#include <list>
#include <random>
#include <stdio.h>
#include <iostream>

#include "Gamemode.h"

#define NON_REFREGIRATED_CONTAINER_COUNT	16
#define REFREGIRATED_CONTAINER_COUNT		8
#define PLAYER_COUNT						2

/**************************************************************************/
/* StorageWars is a turn-based Tetris-like game where two opponents must  */
/* manage their storage while trying to fill the opponent's one. Each     */
/* turn, a new object is spawned and must be either stored or sent to the */
/* opponent's storage. If stored, the player can choose a stored object   */
/* and send it out to the opponent. The first player that gets a container*/
/* fully loaded container that requires dropping an object looses.        */
/**************************************************************************/

int main()
{
	Gamemode* gamemode = new Gamemode();
	gamemode->setNonRefridgerationContainerCount(NON_REFREGIRATED_CONTAINER_COUNT);
	gamemode->setRefridgerationContainerCount(REFREGIRATED_CONTAINER_COUNT);
	gamemode->setupPlayers(PLAYER_COUNT);
	return gamemode->startGame();
}
