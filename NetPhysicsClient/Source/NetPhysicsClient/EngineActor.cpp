#include "NetPhysicsClient.h"
#include "EngineActor.h"
#include "XSource/Handle.h"

AEngineActor::AEngineActor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEngineActor::BeginPlay() {
	Super::BeginPlay();
	engine.init(GetWorld());
}

void AEngineActor::Tick(float DeltaSeconds) {
	engine.update(DeltaSeconds);
}