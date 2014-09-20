#include "netcompmanager.h"
#include "NetworkIDManager.h"

NetworkComponent* NetworkComponentManager::createNewComponent(RakNet::RakPeerInterface *peer,RakNet::NetworkIDManager* manager, RakNet::RakNetGUID guid) {
	//NetworkComponent* newNetworkComponent =  new NetworkComponent(peer, guid);
	//newNetworkComponent->SetNetworkIDManager(manager);
	//networkComponents.push_back(newNetworkComponent);
	//return &networkComponents.back();
	return 0;
}