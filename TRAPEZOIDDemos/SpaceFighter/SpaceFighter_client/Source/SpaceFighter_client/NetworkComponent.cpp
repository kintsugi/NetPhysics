#include "SpaceFighter_client.h"
#include "NetworkComponent.h"
#include "AllowWindowsPlatformTypes.h"
#include "NetworkIDManager.h"
#include "HideWindowsPlatformTypes.h"
#include "HandleManager.h"

NetworkComponent::NetworkComponent(HandleManager& handleManager, RakNet::NetworkIDManager &networkIDManager, RakNet::RakPeerInterface* peer) :
	handle(handleManager.add(this, NETWORK_COMPONENT)),
	RakPeerInstance(peer),
	formatter(NULL) 
{
	SetNetworkIDManager(&networkIDManager);
}

NetworkComponent::NetworkComponent(HandleManager& handleManager, RakNet::NetworkIDManager &networkIDManager, RakNet::RakPeerInterface* peer, StreamFormatter* newFormatter) :
	handle(handleManager.add(this, NETWORK_COMPONENT)),
	RakPeerInstance(peer),
	formatter(newFormatter)
{
	SetNetworkIDManager(&networkIDManager);
}

void NetworkComponent::addBitStream(TSharedPtr<RakNet::BitStream> inBS) {
	streams.Add(Stream(inBS, formatter));
}

TArray<Stream> NetworkComponent::getAllStreams() {
	return streams;
}

TArray<Stream> NetworkComponent::getStreamsOfType(StreamType type) {
	TArray<Stream> ret;
	for (auto iter = streams.CreateIterator(); iter; iter++) {
		if (iter->getStreamData()->type == type)
			ret.Add(*iter);
	}
	return ret;
}

void NetworkComponent::removeAllStreams() {
	streams.Reset();
}

void NetworkComponent::removeStreamsOfType(StreamType type) {
	for (auto iter = streams.CreateIterator(); iter; iter++) {
		if (iter->getStreamData()->type == type) {
			streams.RemoveAt(iter.GetIndex());
			iter--;
		}
	}
}

RakNet::RakPeerInterface* NetworkComponent::getRakPeerInstance() {
	return RakPeerInstance;
}

Handle NetworkComponent::getHandle() {
	return handle;
}