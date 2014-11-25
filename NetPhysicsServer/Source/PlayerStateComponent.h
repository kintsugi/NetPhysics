#ifndef PLAYER_STATE_COMPONENT_H_INCLUDED
#define PLAYER_STATE_COMPONENT_H_INCLUDED

#include "component.h"
#include "handle.h"

class HandleManager;

enum PlayerState {
	UNINITIALIZED,
	INITIALIZED,
	HAS_OBJECT,
};

class PlayerStateComponent : public Component {
public:
	/*
	@param handleManager reference to a handleManager to manage this object
	@param initialState the initial state of the player
	*/
	PlayerStateComponent(HandleManager &handleManager,
						 PlayerState initialState);

	//Returns the player's state.
	PlayerState getState() const;

	//Sets the player's state.
	void setState(const PlayerState newState);

private:

	//Player's current state
	PlayerState state;
};

#endif