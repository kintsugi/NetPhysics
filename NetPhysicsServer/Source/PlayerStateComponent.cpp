#include "PlayerStateComponent.h"
#include "HandleManager.h"
#include "ComponentType.h"

using namespace NetPhysics;

PlayerStateComponent::PlayerStateComponent(
	PlayerState initialState)
	: Component(PLAYER_STATE_COMPONENT)
	, state(initialState)
{}

PlayerState PlayerStateComponent::getState() const {
	return state;
}

void PlayerStateComponent::setState(const PlayerState newState) {
	state = newState;
}