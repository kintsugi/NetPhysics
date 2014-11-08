#ifndef PLAYER_STATE_MANAGER_H_INCLUDED
#define PLAYER_STATE_MANAGER_H_INCLUDED

#include "xlib.h"
#include "handle.h"
#include "playerstatecomponent.h"

typedef std::shared_ptr<PlayerStateComponent> PlayerStateComponentPtr;

class HandleManager;

class PlayerStateManager {
public:
	void update(HandleManager &handleManager);
	Handle createComponent(HandleManager &handleManager, PlayerState initialState);

private:
	XLib::Vector<PlayerStateComponentPtr> container;
};

#endif