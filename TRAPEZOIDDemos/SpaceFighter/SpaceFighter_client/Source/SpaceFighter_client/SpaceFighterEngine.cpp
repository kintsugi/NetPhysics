#include "SpaceFighter_client.h"
#include "SpaceFighterEngine.h"
#include "NetworkMessages.h"
#include "TestActor.h"

ASpaceFighterEngine::ASpaceFighterEngine(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP) {
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceFighterEngine::BeginPlay() {
	Super::BeginPlay();
	connectionSystem.connect();

}

void ASpaceFighterEngine::Tick(float dt) {
	Super::Tick(dt);
	networkManager.update(handleManager);
	handlePackets(connectionSystem.getPackets());
}

void ASpaceFighterEngine::handlePackets(TArray<TSharedPtr<RakNet::Packet>> packets) {
	for (auto iter = packets.CreateIterator(); iter; iter++) {
		RakNet::Packet* packet = iter->Get();
		switch (packet->data[0]) {
		case START_PLAYER: {
			RakNet::BitStream bsIn(packet->data, packet->length, false);
			NetworkMessage msg;
			bsIn.Read(msg);
			RakNet::NetworkID networkID;
			uint32 l = sizeof(RakNet::MessageID) + sizeof(RakNet::NetworkID);
			bsIn.Read(networkID);
			spawnNetworkActor<ATestActor>(networkID);
			break;
		}
		case NETWORK_COMPONENT_MESSAGE: {
			networkSystem.sendToNetworkComponent(networkIDManager, handleManager, *iter);
		}

		
		}
	}
}