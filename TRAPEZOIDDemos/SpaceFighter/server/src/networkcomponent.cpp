#include "networkcomponent.h"
#include "handlemanager.h"

NetworkComponent::NetworkComponent(HandleManager* handleManager, RakNet::RakPeerInterface* peer) : 
	handle(handleManager->add(this, NETWORK_COMPONENT)),
	RakNetInstance(peer) {}

void NetworkComponent::addStream(std::shared_ptr<RakNet::BitStream> inStream) {
	receivedStreams.push_back(inStream);
}
std::vector<std::shared_ptr<RakNet::BitStream>> NetworkComponent::getReceivedStreams() {
	auto ret = receivedStreams;
	receivedStreams.clear();
	return ret;
}
RakNet::RakPeerInterface* NetworkComponent::getRakNetInstance() {
	return RakNetInstance;
}

Handle NetworkComponent::getHandle() {
	return handle;
}