#include "SpaceFighter_client.h"
#include "SpaceFighterEngine.h"
#include "NetworkMessages.h"
#include "TestActor.h"
#include "NativeTypes.h"

ASpaceFighterEngine::ASpaceFighterEngine(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP) {
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceFighterEngine::BeginPlay() {
	Super::BeginPlay();
	connectionSystem.connect();

}

void ASpaceFighterEngine::Tick(float dt) {
	Super::Tick(dt);
	connectionSystem.update();
	networkManager.update(handleManager);
	handlePackets(connectionSystem.getPackets());
}

void ASpaceFighterEngine::handlePackets(TArray<PacketToBitStream> packets) {
	for (auto iter = packets.CreateIterator(); iter; iter++) {
		switch (iter->messageID) {
		case START_PLAYER: {
			iter->bitStream->IgnoreBytes(sizeof(RakNet::MessageID));
			RakNet::NetworkID networkID;
			iter->bitStream->Read(networkID);
			spawnNetworkActor<ATestActor>(networkID);
			break;
		}
		case NETWORK_COMPONENT_MESSAGE: {
			networkSystem.sendToNetworkComponent(networkIDManager, handleManager, *iter);
		}

		
		}
	}
}