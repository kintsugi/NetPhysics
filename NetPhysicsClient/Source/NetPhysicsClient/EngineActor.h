#pragma once

#include "ClientEngine.h"

//UE Includes
#include "GameFramework/Actor.h"
#include "EngineActor.generated.h"

UCLASS()
class NETPHYSICSCLIENT_API AEngineActor : public AActor
{
	GENERATED_UCLASS_BODY()
public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:

	NetPhysics::ClientEngine engine;
};
