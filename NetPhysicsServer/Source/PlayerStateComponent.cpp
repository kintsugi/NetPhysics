#include "PlayerStateComponent.h"
#include "HandleManager.h"
#include "ComponentType.h"

PlayerStateComponent::PlayerStateComponent(HandleManager &handleManager, PlayerState initialState) : 
Component(PLAYER_STATE, handleManager.add(this, COMPONENT)),
	state(initialState) {}

PlayerState PlayerStateComponent::getState() const {
	return state;
}

void PlayerStateComponent::setState(const PlayerState newState) {
	state = newState;
}