#include "SpaceFighter_client.h"
#include "networkcomponent.h"
#include "handlemanager.h"

NetworkComponent::NetworkComponent(HandleManager& handleManager,
	RakNet::NetworkIDManager &networkIDManager,
	RakNet::RakPeerInterface* peer)
	: handle(handleManager.add(this, NETWORK_COMPONENT)),
	RakPeerInstance(peer),
	formatter(NULL) {
	SetNetworkIDManager(&networkIDManager);
}

NetworkComponent::NetworkComponent(HandleManager& handleManager,
	RakNet::NetworkIDManager &networkIDManager,
	RakNet::RakPeerInterface* peer,
	TSharedPtr<StreamFormatter> newFormatter)
	: handle(handleManager.add(this, NETWORK_COMPONENT)),
	RakPeerInstance(peer),
	formatter(newFormatter) {
	SetNetworkIDManager(&networkIDManager);
}

void NetworkComponent::setFormatter(TSharedPtr<StreamFormatter> newFormatter) {
	formatter = newFormatter;
}

TSharedPtr<StreamFormatter> NetworkComponent::getFormatter() {
	return formatter;
}

void NetworkComponent::addBitStream(TSharedPtr<RakNet::BitStream> inBS) {
	inBitStreams.Add(inBS);
}

TArray<TSharedPtr<RakNet::BitStream>> NetworkComponent::getBitStreams() {
	return inBitStreams;
}

TSharedPtr<RakNet::BitStream> NetworkComponent::popBitStream() {
	return inBitStreams.Pop();
}

void NetworkComponent::clearBitStreams() {
	inBitStreams.Reset();
}

RakNet::RakPeerInterface* NetworkComponent::getRakPeerInstance() const {
	return RakPeerInstance;
}

Handle NetworkComponent::getHandle() const {
	return handle;
}