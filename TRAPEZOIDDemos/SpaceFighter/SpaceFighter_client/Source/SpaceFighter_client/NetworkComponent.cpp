#include "SpaceFighter_client.h"
#include "NetworkComponent.h"
#include "HandleManager.h"

NetworkComponent::NetworkComponent(HandleManager* handleManager, RakNet::RakPeerInterface* peer)
	: handle(handleManager->add(this, NETWORK_COMPONENT)),
	RakNetInstance(peer) {
}

void NetworkComponent::addStream(TSharedPtr<RakNet::BitStream> inStream) {
	receivedStreams.Add(inStream);
}
TArray<TSharedPtr<RakNet::BitStream>> NetworkComponent::getReceivedStreams() {
	auto ret = receivedStreams;
	receivedStreams.Reset();
	return ret;
}
RakNet::RakPeerInterface* NetworkComponent::getRakNetInstance() {
	return RakNetInstance;
}

Handle NetworkComponent::getHandle() {
	return handle;
}