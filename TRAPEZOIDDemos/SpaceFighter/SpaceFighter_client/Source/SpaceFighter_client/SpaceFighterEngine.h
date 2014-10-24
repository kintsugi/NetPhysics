

#pragma once

#include "GameFramework/Actor.h"
#include "ConnectionSystem.h"
#include "HandleManager.h"
#include "SpaceFighterEngine.generated.h"

/*
	Main actor class to implement the Space Fighter game.
*/
UCLASS()
class ASpaceFighterEngine : public AActor
{
	GENERATED_UCLASS_BODY()
	virtual void BeginPlay() override;
	virtual void Tick(float dt) override;
	//Managers
	HandleManager handleManager;
	//Systems
	ConnectionSystem connectionSystem;

	//Utility functions
	void handleStreams(TArray<TSharedPtr<RakNet::BitStream>> packets);
	
};

struct testMessage {
	int type;
	FString test;
};