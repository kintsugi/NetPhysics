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
#ifdef NET_PHYSICS_SERVER
	inBitStreams.push_back(inBS);
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	inBitStreams.Add(inBS);
#endif /* NET_PHYSICS_CLIENT */
}

XLib::Vector<XLib::SharedPtr<RakNet::BitStream>> NetworkComponent::getBitStreams() const {
	return inBitStreams;
}

XLib::SharedPtr<RakNet::BitStream> NetworkComponent::popBitStream() {
#ifdef NET_PHYSICS_SERVER
	XLib::SharedPtr<RakNet::BitStream> ret = inBitStreams.back();
	inBitStreams.pop_back();
	return ret;
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	return inBitStreams.Pop();
#endif /* NET_PHYSICS_CLIENT */
}

void NetworkComponent::clearBitStreams() {
#ifdef NET_PHYSICS_SERVER
	inBitStreams.clear();
#endif
#ifdef NET_PHYSICS_CLIENT
	inBitStreams.Reset();
#endif
}

RakNet::RakPeerInterface* NetworkComponent::getRakPeerInstance() const {
	return RakPeerInstance;
}