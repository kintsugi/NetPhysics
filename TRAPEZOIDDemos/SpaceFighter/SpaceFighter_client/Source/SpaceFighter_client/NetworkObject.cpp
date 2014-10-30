#include "SpaceFighter_client.h"
#include "NetworkObject.h"
#include "HandleManager.h"
#include "NetworkComponent.h"

NetworkObject::~NetworkObject() {
	handleManager->remove(handle);
	handleManager->remove(networkComponentHandle);
}

void NetworkObject::init(HandleManager* handleManagerPtr, Handle newNetCompHandle) {
	handle = handleManagerPtr->add(this, NETWORK_OBJECT);
	handleManager = handleManagerPtr;
	networkComponentHandle = newNetCompHandle;
}

Handle NetworkObject::getHandle() {
	return handle;
}

NetworkComponent* NetworkObject::getNetworkComponent() {
	if (handleManager && networkComponentHandle.type == NETWORK_COMPONENT)
		return (NetworkComponent*)handleManager->get(networkComponentHandle);
	return false;
}

RakNet::NetworkID NetworkObject::getNetworkID() {
	NetworkComponent* netComp = getNetworkComponent();
	if (netComp)
		return netComp->GetNetworkID();
	else 
		return 0;
}

bool NetworkObject::setNetworkID(RakNet::NetworkID networkID) {
	NetworkComponent* netComp = getNetworkComponent();
	if (netComp) {
		netComp->SetNetworkID(networkID);
		return true;
	} else
		return false;
}