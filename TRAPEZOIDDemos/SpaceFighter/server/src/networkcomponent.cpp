#include "networkcomponent.h"
#include "handlemanager.h"

NetworkComponent::NetworkComponent(HandleManager& handleManager,
								   RakNet::NetworkIDManager &networkIDManager,
								   RakNet::RakPeerInterface* peer)
	: handle(handleManager.add(this, NETWORK_COMPONENT)),
	  RakPeerInstance(peer),
	  formatter(NULL)
{
	SetNetworkIDManager(&networkIDManager);
}

NetworkComponent::NetworkComponent(HandleManager& handleManager,
								   RakNet::NetworkIDManager &networkIDManager,
								   RakNet::RakPeerInterface* peer,
								   std::shared_ptr<StreamFormatter> newFormatter)
	: handle(handleManager.add(this, NETWORK_COMPONENT)),
	  RakPeerInstance(peer),
	  formatter(newFormatter)
{
	SetNetworkIDManager(&networkIDManager);
}

void NetworkComponent::setFormatter(std::shared_ptr<StreamFormatter> newFormatter) {
	formatter = newFormatter;
}

std::shared_ptr<StreamFormatter> NetworkComponent::getFormatter() {
	return formatter;
}

void NetworkComponent::addBitStream(std::shared_ptr<RakNet::BitStream> inBS) {
	inBitStreams.push_back(inBS);
}

std::vector<std::shared_ptr<RakNet::BitStream>> NetworkComponent::getBitStreams() {
	return inBitStreams;
}

std::shared_ptr<RakNet::BitStream> NetworkComponent::popBitStream() {
	std::shared_ptr<RakNet::BitStream> ret = inBitStreams.back();
	inBitStreams.pop_back();
	return ret;
}

void NetworkComponent::clearBitStreams() {
	inBitStreams.clear();
}

RakNet::RakPeerInterface* NetworkComponent::getRakPeerInstance() const {
	return RakPeerInstance;
}

Handle NetworkComponent::getHandle() const {
	return handle;
}