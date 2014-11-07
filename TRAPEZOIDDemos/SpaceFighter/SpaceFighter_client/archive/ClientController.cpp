#include "SpaceFighter_client.h"
#include "ClientController.h"
#include "NetworkComponent.h"
#include "NetworkMessage.h"

AClientController::AClientController(const FPostConstructInitializeProperties &PCIP) : Super(PCIP) {
	serverGUID = RakNet::RakNetGUID();
}

void AClientController::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	destroyNetworkObject();
}

void AClientController::networkUpdate() {}

void AClientController::setServerGUID(RakNet::RakNetGUID newServerGUID) {
	serverGUID = newServerGUID;
}

void AClientController::disconnect() {
	if (serverGUID != RakNet::RakNetGUID()) {
		RakNet::RakPeerInterface* peer = getNetworkComponent()->getRakPeerInstance();
		NetworkMessage::Package package(peer, serverGUID);
		NetworkMessage::Send::clientDisconnect(package, getNetworkKey());
	}
}