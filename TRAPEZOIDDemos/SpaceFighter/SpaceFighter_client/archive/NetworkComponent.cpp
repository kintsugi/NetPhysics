#include "SpaceFighter_client.h"
#include "networkcomponent.h"
#include "HandleManager.h"

NetworkComponent::NetworkComponent(HandleManager& handleManager, 
								   NetworkHandleManager &networkHandleManager,
								   RakNet::RakPeerInterface* peer)
	: Component(handleManager.add(this, NETWORK_COMPONENT)),
	  NetworkHandleObject(this),
	  RakPeerInstance(peer),
	  formatter(NULL)
{
	setNetworkHandleManager(networkHandleManager);
}

NetworkComponent::NetworkComponent(HandleManager& handleManager,
								   NetworkHandleManager &networkHandleManager,
								   RakNet::RakPeerInterface* peer,
								   StreamFormatter* newFormatter)
	: Component(handleManager.add(this, NETWORK_COMPONENT)),
	  NetworkHandleObject(this),
	  RakPeerInstance(peer),
	  formatter(newFormatter)
{
	setNetworkHandleManager(networkHandleManager);
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