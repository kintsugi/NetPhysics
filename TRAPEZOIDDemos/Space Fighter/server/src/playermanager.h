#ifndef PLAYER_MANAGER_H_INCLUDED
#define PLAYER_MANAGER_H_INCLUDED

#include <vector>
#include "player.h"

/*
	Holds a copy of each player that is currently playing on the server.
	Manages updates to players on the scale of the entire client rather than
	just their corresponding entity, such as state changes, creating and
	deleting entities when someone connects or disconnects.
*/
class PlayerManager {
public:
	PlayerManager() {

	}

	void update();
private:
	std::vector<Player> players;
};

#endif