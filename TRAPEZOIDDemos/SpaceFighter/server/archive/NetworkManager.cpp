#include "networkmanager.h"
#include "handlemanager.h"
#include "networkhandlemanager.h"
#include "engineregister.h"

void NetworkManager::update(HandleManager &handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager.get((*iter)->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}

Handle NetworkManager::createComponent(EngineRegister &engineRegister, RakNet::RakPeerInterface* peer) {
	//Get managers from engine registers
	HandleManager* handleManager = engineRegister.getManager<HandleManager>(HANDLE_MANAGER);
	NetworkHandleManager *networkIDManager = engineRegister.getManager<NetworkHandleManager>(NETWORK_HANDLE_MANAGER);


	container.push_back(NetworkComponentPtr(new NetworkComponent(*handleManager, *networkIDManager, peer)));
	return container.back()->getHandle();
}