#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif
#include "NetworkComponent.h"
#include "HandleManager.h"
#include "ComponentType.h"

using namespace NetPhysics;

NetworkComponent::NetworkComponent(
	NetworkHandleManager &networkHandleManager,
	RakNet::RakPeerInterface* peer) 
	: Component(NETWORK_COMPONENT)
	, NetworkHandleObject(this)
	, RakPeerInstance(peer)
	, formatter(nullptr)
{
	setNetworkHandleManager(networkHandleManager);
}

NetworkComponent::NetworkComponent(
	NetworkHandleManager &networkHandleManager,
	RakNet::RakPeerInterface* peer,
	StreamFormatter* newFormatter)
	: Component(NETWORK_COMPONENT)
	, NetworkHandleObject(this)
	, RakPeerInstance(peer)
	, formatter(newFormatter)
{
	setNetworkHandleManager(networkHandleManager);
}

void NetworkComponent::setFormatter(
	std::shared_ptr<StreamFormatter> newFormatter)
{
	formatter = newFormatter;
}

std::shared_ptr<StreamFormatter> NetworkComponent::getFormatter() const {
	return formatter;
}

void NetworkComponent::addBitStream(std::shared_ptr<RakNet::BitStream> inBS) {
	inBitStreams.push_back(inBS);
}

std::vector<std::shared_ptr<RakNet::BitStream>> NetworkComponent::getBitStreams() const {
	return inBitStreams;
}

std::shared_ptr<RakNet::BitStream> NetworkComponent::popBitStream() {
	std::shared_ptr<RakNet::BitStream> ret(new RakNet::BitStream());
	ret->Write(inBitStreams.back().get(), inBitStreams.back()->GetNumberOfBytesUsed());
	inBitStreams.pop_back();
	return ret;
}

void NetworkComponent::clearBitStreams() {
	inBitStreams.clear();
}

RakNet::RakPeerInterface* NetworkComponent::getRakPeerInstance() const {
	return RakPeerInstance;
}