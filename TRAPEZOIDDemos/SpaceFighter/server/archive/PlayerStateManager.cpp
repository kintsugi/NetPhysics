#include "PlayerStateManager.h"
#include "handlemanager.h"

void PlayerStateManager::update(HandleManager &handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager.get((*iter)->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}

Handle PlayerStateManager::createComponent(HandleManager &handleManager, PlayerState initialState) {
	container.push_back(PlayerStateComponentPtr(new PlayerStateComponent(handleManager, initialState)));
	return container.back()->getHandle();
}