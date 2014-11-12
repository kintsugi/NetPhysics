#ifdef CLIENT
	#include UE4_PROJECT_H
#endif
#include "HandleManager.h"
#include "NetworkComponent.h"

NetworkComponent::NetworkComponent(HandleManager &handleManager,
								   NetworkHandleManager &networkHandleManager,
								   RakNet::RakPeerInterface* peer)
	: Component(handleManager.add(this, NETWORK_COMPONENT_HANDLE)),
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
	: Component(handleManager.add(this, NETWORK_COMPONENT_HANDLE)),
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
#ifdef SERVER
	inBitStreams.push_back(inBS);
#endif /* SERVER */
#ifdef CLIENT
	inBitStreams.Add(inBS);
#endif /* CLIENT */
}

XLib::Vector<XLib::SharedPtr<RakNet::BitStream>> NetworkComponent::getBitStreams() {
	return inBitStreams;
}

XLib::SharedPtr<RakNet::BitStream> NetworkComponent::popBitStream() {
#ifdef SERVER
	XLib::SharedPtr<RakNet::BitStream> ret = inBitStreams.back();
	inBitStreams.pop_back();
	return ret;
#endif /* SERVER */
#ifdef CLIENT
	return inBitStreams.Pop();
#endif /* CLIENT */
}

void NetworkComponent::clearBitStreams() {
#ifdef SERVER
	inBitStreams.clear();
#endif
#ifdef CLIENT
	inBitStreams.Reset();
#endif
}

RakNet::RakPeerInterface* NetworkComponent::getRakPeerInstance() const {
	return RakPeerInstance;
}