#include "SpaceFighter_client.h"
#include "SpaceFighterEngine.h"
#include "Messenger.h"
#include "BitStream.h"


ASpaceFighterEngine::ASpaceFighterEngine(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP) {
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceFighterEngine::BeginPlay() {
	Super::BeginPlay();
	connectionSystem.connect();
}


void ASpaceFighterEngine::Tick(float dt) {
	Super::Tick(dt);
	handlePackets(connectionSystem.getPackets());
}

void ASpaceFighterEngine::handlePackets(TArray<TSharedPtr<RakNet::Packet>> inBitStreams) {
	for (auto iter = inBitStreams.CreateIterator(); iter; iter++) {
	}
}