#ifndef PLAYER_STATE_COMPONENT_H_INCLUDED
#define PLAYER_STATE_COMPONENT_H_INCLUDED

#include "handle.h"

class HandleManager;

enum PlayerState {
	UNINITIALIZED,
	INITIALIZED,
};

class PlayerStateComponent {
public:
	/*
	@param handleManager reference to a handleManager to manage this object
	@param initialState the initial state of the player
	*/
	PlayerStateComponent(HandleManager &handleManager, PlayerState initialState);

	//Returns the player's state.
	PlayerState getState() const;

	//Sets the player's state.
	void setState(const PlayerState newState);

	//Gets this object's handle.
	Handle getHandle() const;
private:
	//Handle of this object.
	Handle handle;

	//Player's current state
	PlayerState state;
};

#endif