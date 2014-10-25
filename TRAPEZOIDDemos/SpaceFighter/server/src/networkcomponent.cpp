#include "networkcomponent.h"
#include "handlemanager.h"

NetworkComponent::NetworkComponent(HandleManager& handleManager, RakNet::RakPeerInterface* peer) :
	handle(handleManager.add(this, NETWORK_COMPONENT)),
	RakPeerInstance(peer),
	formatter(NULL) {}

NetworkComponent::NetworkComponent(HandleManager& handleManager, RakNet::RakPeerInterface* peer, StreamFormatter* newFormatter) :
	handle(handleManager.add(this, NETWORK_COMPONENT)),
	RakPeerInstance(peer),
	formatter(newFormatter){}

void NetworkComponent::addBitStream(std::shared_ptr<RakNet::BitStream> inBS) {
	streams.push_back(Stream(inBS, formatter));
}

std::vector<Stream> NetworkComponent::getAllStreams() {
	return streams;
}

std::vector<Stream> NetworkComponent::getStreamsOfType(StreamType type) {
	std::vector<Stream> ret;
	for (auto iter = streams.begin(); iter != streams.end(); iter++) {
		if (iter->getStreamData()->type == type)
			ret.push_back(*iter);
	}
	return ret;
}

void NetworkComponent::removeAllStreams() {
	streams.clear();
}

void NetworkComponent::removeStreamsOfType(StreamType type) {
	for (auto iter = streams.begin(); iter != streams.end(); iter++) {
		if (iter->getStreamData()->type == type)
			iter = streams.erase(iter);
	}
}

RakNet::RakPeerInterface* NetworkComponent::getRakPeerInstance() {
	return RakPeerInstance;
}

Handle NetworkComponent::getHandle() {
	return handle;
}