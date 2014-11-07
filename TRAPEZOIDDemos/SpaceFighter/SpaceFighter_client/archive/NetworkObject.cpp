#include "SpaceFighter_client.h"
#include "NetworkObject.h"
#include "HandleManager.h"
#include "NetworkComponent.h"

void NetworkObject::init(HandleManager* handleManagerPtr, Handle newNetCompHandle) {
	handle = handleManagerPtr->add(this, NETWORK_OBJECT);
	handleManager = handleManagerPtr;
	networkComponentHandle = newNetCompHandle;
}

void NetworkObject::destroyNetworkObject() {
	if (handleManager) {
		if (handleManager->get(handle)) {
			handleManager->remove(handle);
			handleManager->remove(networkComponentHandle);
		}
	}
}

Handle NetworkObject::getHandle() {
	return handle;
}

NetworkComponent* NetworkObject::getNetworkComponent() {
	if (handleManager)
		return (NetworkComponent*)handleManager->get(networkComponentHandle);
	return NULL;
}

NetworkKey NetworkObject::getNetworkKey() {
	NetworkComponent* netComp = getNetworkComponent();
	if (netComp)
		return netComp->getNetworkKey();
	else 
		return 0;
}

bool NetworkObject::setNetworkKey(NetworkKey networkKey) {
	NetworkComponent* netComp = getNetworkComponent();
	if (netComp) {
		netComp->setNetworkKey(networkKey);
		return true;
	} else
		return false;
}