#include "networkcomponent.h"
#include "handlemanager.h"

#include "NetworkIDManager.h"

NetworkComponent::NetworkComponent(HandleManager &handleManager,
								   NetworkHandleManager &networkHandleManager,
								   RakNet::RakPeerInterface* peer)
	: Component(handleManager.add(this, NETWORK_COMPONENT)),
	  NetworkHandleObject(this),
	  RakPeerInstance(peer),
	  formatter(NULL)
{
	setNetworkHandleManager(networkHandleManager);
}

NetworkComponent::NetworkComponent(HandleManager &handleManager,
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

void NetworkComponent::setFormatter(XLib::SharedPtr<StreamFormatter> newFormatter) {
	formatter = newFormatter;
}

XLib::SharedPtr<StreamFormatter> NetworkComponent::getFormatter() {
	return formatter;
}

void NetworkComponent::addBitStream(XLib::SharedPtr<RakNet::BitStream> inBS) {
	inBitStreams.push_back(inBS);
}

std::vector<std::shared_ptr<RakNet::BitStream>> NetworkComponent::getBitStreams() {
	return inBitStreams;
}

XLib::SharedPtr<RakNet::BitStream> NetworkComponent::popBitStream() {
	XLib::SharedPtr<RakNet::BitStream> ret = inBitStreams.back();
	inBitStreams.pop_back();
	return ret;
}

void NetworkComponent::clearBitStreams() {
	inBitStreams.clear();
}

RakNet::RakPeerInterface* NetworkComponent::getRakPeerInstance() const {
	return RakPeerInstance;
}