#include "SpaceFighter_client.h"
#include "NetworkManager.h"
#include "Handlemanager.h"

void NetworkManager::update(HandleManager &handleManager) {
	for (auto iter = container.CreateIterator(); iter;iter++) {
		if (!handleManager.get((*iter)->getHandle())) {
			container.RemoveAt(iter.GetIndex());
			iter--;
		}
	}
}

Handle NetworkManager::createComponent(HandleManager &handleManager, RakNet::NetworkIDManager &networkIDManager, RakNet::RakPeerInterface* peer) {
	container.Add(NetworkComponentPtr(new NetworkComponent(handleManager, networkIDManager, peer)));
	return container.Last()->getHandle();
}