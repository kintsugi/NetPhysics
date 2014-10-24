#include "SpaceFighter_client.h"
#include "SpaceFighterEngine.h"
#include "Messenger.h"


ASpaceFighterEngine::ASpaceFighterEngine(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP) {
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceFighterEngine::BeginPlay() {
	Super::BeginPlay();
	connectionSystem.connect();
}


void ASpaceFighterEngine::Tick(float dt) {
	Super::Tick(dt);
	handleStreams(connectionSystem.getStreams());
}

void ASpaceFighterEngine::handleStreams(TArray<TSharedPtr<RakNet::BitStream>> packets) {
	for (auto iter = packets.CreateIterator(); iter; iter++) {

	}
}