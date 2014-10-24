#include "clientmanager.h"
#include "handlemanager.h"

void ClientManager::update(HandleManager* handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager->get(iter->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}

Handle ClientManager::createComponent(HandleManager* handleManager, RakNet::RakNetGUID guid) {
	container.push_back(ClientComponent(handleManager, guid));
	return container.back().getHandle();
}