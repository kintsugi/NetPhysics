#include "clientcomponent.h"

ClientComponent::ClientComponent(HandleManager &handleManager, RakNet::RakPeerInterface *peer, const RakNet::RakNetGUID newClientGUID) :
	handle(handleManager.add(this, CLIENT_COMPONENT)),
	RakPeerInstance(peer),
	clientGUID(newClientGUID) {}

RakNet::RakNetGUID ClientComponent::getClientGUID() const {
	return clientGUID;
}

RakNet::ConnectionState ClientComponent::getConnectionState() const {
	return RakPeerInstance->GetConnectionState(clientGUID);
}

Handle ClientComponent::getHandle() const {
	return handle;
}