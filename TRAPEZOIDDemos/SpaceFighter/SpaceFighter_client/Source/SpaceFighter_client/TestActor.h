#pragma once

#include "NetworkObject.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

UCLASS()
class ATestActor : public AActor, public NetworkObject {
	GENERATED_UCLASS_BODY()

	virtual void networkUpdate();

	UPROPERTY()
	int32 test = 0;
};