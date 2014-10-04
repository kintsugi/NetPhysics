#include "networkmanager.h"
#include "handlemanager.h"

void NetworkManager::update(HandleManager* handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager->get(iter->get()->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}

Handle NetworkManager::createComponent(HandleManager* handleManager, RakNet::RakPeerInterface* peer, RakNet::NetworkIDManager* networkIDManager) {
	std::unique_ptr<NetworkComponent> newComponent(new NetworkComponent(peer, networkIDManager));
	container.push_back(std::move(newComponent));
	container.back().get()->setHandle(handleManager->add(container.back().get(), NETWORK));
	return container.back().get()->getHandle();
}