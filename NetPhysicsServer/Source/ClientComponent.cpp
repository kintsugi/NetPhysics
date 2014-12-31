#include "ClientComponent.h"
#include "HandleManager.h"
#include "ComponentType.h"
#ifdef NET_PHYSICS_CLIENT
	#include "AllowWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
	#include "RakPeerInterface.h"
#ifdef NET_PHYSICS_CLIENT
	#include "HideWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */

using namespace NetPhysics;

ClientComponent::ClientComponent(
	RakNet::RakPeerInterface *peer, 
	const RakNet::RakNetGUID newClientGUID)
	: Component(CLIENT_COMPONENT)
	, RakPeerInstance(peer)
	, clientGUID(newClientGUID) 
{}

RakNet::RakNetGUID ClientComponent::getClientGUID() const {
	return clientGUID;
}

RakNet::ConnectionState ClientComponent::getConnectionState() const {
	return RakPeerInstance->GetConnectionState(clientGUID);
}