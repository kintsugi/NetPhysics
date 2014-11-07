#pragma once

#include "NetworkObject.h"
#include "AllowWindowsPlatformTypes.h"
#include "RakNetTypes.h"
#include "HideWindowsPlatformTypes.h"
#include "GameFramework/Actor.h"
#include "ClientController.generated.h"

UCLASS()
class AClientController : public AActor, public NetworkObject {
	GENERATED_UCLASS_BODY()
public:

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void networkUpdate();

	void setServerGUID(RakNet::RakNetGUID newServerGUID);

	UFUNCTION()
	void disconnect();

private:
	RakNet::RakNetGUID serverGUID;
};