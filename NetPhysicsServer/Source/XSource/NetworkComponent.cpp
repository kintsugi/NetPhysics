#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif
#include "NetworkComponent.h"
#include "HandleManager.h"
#include "ComponentType.h"

using namespace NetPhysics;

NetworkComponent::NetworkComponent(
	HandleManager &handleManager,
	NetworkHandleManager &networkHandleManager,
	RakNet::RakPeerInterface* peer) 
	: Component(NETWORK_COMPONENT
	, handleManager.add(this, COMPONENT))
	, NetworkHandleObject(this)
	, RakPeerInstance(peer)
	, formatter(nullptr)
{
	setNetworkHandleManager(networkHandleManager);
}

NetworkComponent::NetworkComponent(
	HandleManager &handleManager,
	NetworkHandleManager &networkHandleManager,
	RakNet::RakPeerInterface* peer,
	StreamFormatter* newFormatter)
	: Component(NETWORK_COMPONENT, handleManager.add(this, COMPONENT))
	, NetworkHandleObject(this)
	, RakPeerInstance(peer)
	, formatter(newFormatter)
{
	setNetworkHandleManager(networkHandleManager);
}

void NetworkComponent::setFormatter(
	XLib::SharedPtr<StreamFormatter> newFormatter)
{
	formatter = newFormatter;
}

XLib::SharedPtr<StreamFormatter> NetworkComponent::getFormatter() const {
	return formatter;
}

void NetworkComponent::addBitStream(XLib::SharedPtr<RakNet::BitStream> inBS) {
	inBitStreams.push_back(inBS);
}

XLib::Vector<XLib::SharedPtr<RakNet::BitStream>> NetworkComponent::getBitStreams() const {
	return inBitStreams;
}

XLib::SharedPtr<RakNet::BitStream> NetworkComponent::popBitStream() {
	XLib::SharedPtr<RakNet::BitStream> ret(new RakNet::BitStream());
	RakNet::BitStream* back = &*inBitStreams.back();
	ret->Write(back, inBitStreams.back()->GetNumberOfBytesUsed());
	inBitStreams.pop_back();
	return ret;
}

void NetworkComponent::clearBitStreams() {
	inBitStreams.clear();
}

RakNet::RakPeerInterface* NetworkComponent::getRakPeerInstance() const {
	return RakPeerInstance;
}