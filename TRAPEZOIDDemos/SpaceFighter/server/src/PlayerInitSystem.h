#ifndef PLAYER_INIT_SYSTEM_H_INCLUDED
#define PLAYER_INIT_SYSTEM_H_INCLUDED

#include "gameobjectfilter.h"

class EngineRegister;
class GameObject;

/*
	Checks for new players and inits them. The initial game components are
	created here, setting the rules for the game.
*/
class PlayerInitSystem {
public:
	PlayerInitSystem();
	void update(EngineRegister& engineRegister);

private:

	void init(EngineRegister& engineRegister, GameObject* gameObject);

	GameObjectFilter playerInitFilter;
};

#endif