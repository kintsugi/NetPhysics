#ifndef GAME_STATE_SYSTEM_H_INCLUDED
#define GAME_STATE_SYSTEM_H_INCLUDED

#include "gameobjectfilter.h"

class ManagerRegister;
class GameObject;

/*
	Controls the state of the game
	Sets up new players, cleans up those who disconnect, etc.
*/
class GameStateSystem {
public:
	GameStateSystem();
	void update(ManagerRegister& managerRegister);

private:

	void initializePlayer(ManagerRegister& managerRegister, GameObject* gameObject);

	GameObjectFilter playerStateFilter;
};

#endif