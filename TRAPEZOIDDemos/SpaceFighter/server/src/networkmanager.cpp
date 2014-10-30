#include "networkmanager.h"
#include "handlemanager.h"

void NetworkManager::update(HandleManager &handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager.get((*iter)->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}

Handle NetworkManager::createComponent(HandleManager &handleManager, RakNet::NetworkIDManager &networkIDManager, RakNet::RakPeerInterface* peer) {
	container.push_back(NetworkComponentPtr(new NetworkComponent(handleManager, networkIDManager, peer)));
	return container.back()->getHandle();
}