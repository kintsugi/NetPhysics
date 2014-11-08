#include "playerstatecomponent.h"
#include "handlemanager.h"

PlayerStateComponent::PlayerStateComponent(HandleManager &handleManager, PlayerState initialState) : 
Component(handleManager.add(this, PLAYER_STATE_COMPONENT_HANDLE)),
	state(initialState) {}

PlayerState PlayerStateComponent::getState() const {
	return state;
}

void PlayerStateComponent::setState(const PlayerState newState) {
	state = newState;
}