#ifndef PLAYER_STATE_MANAGER_H_INCLUDED
#define PLAYER_STATE_MANAGER_H_INCLUDED

#include <vector>
#include <memory>
#include "handle.h"
#include "playerstatecomponent.h"

typedef std::shared_ptr<PlayerStateComponent> PlayerStateComponentPtr;

class HandleManager;

class PlayerStateManager {
public:
	void update(HandleManager &handleManager);
	Handle createComponent(HandleManager &handleManager, PlayerState initialState);

private:
	std::vector<PlayerStateComponentPtr> container;
};

#endif