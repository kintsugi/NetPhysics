

#pragma once

#include "GameFramework/Actor.h"

//Managers
#include "AllowWindowsPlatformTypes.h"
#include "NetworkIDManager.h"
#include "HideWindowsPlatformTypes.h"
#include "HandleManager.h"
#include "NetworkManager.h"


//Systems
#include "ConnectionSystem.h"
#include "NetworkSystem.h"
#include "NetworkObject.h"

#include "SpaceFighterEngine.generated.h"


UCLASS()
class ASpaceFighterEngine : public AGameMode
{
	GENERATED_UCLASS_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float dt) override;
	//Managers
	HandleManager handleManager;
	NetworkManager networkManager;
	RakNet::NetworkIDManager networkIDManager;

	//Systems
	ConnectionSystem connectionSystem;
	NetworkSystem networkSystem;

	//Utility functions
	void handlePackets(TArray<TSharedPtr<RakNet::Packet>> packets);

	template <class T>
	T* spawnNetworkActor(RakNet::NetworkID networkID);
	
};

template <class T>
T* ASpaceFighterEngine::spawnNetworkActor(RakNet::NetworkID networkID) {
	T* ret = (T*)GetWorld()->SpawnActor(T::StaticClass());
	NetworkObject* networkObjectPtr = (NetworkObject*)ret;
	Handle networkComponentHandle = networkManager.createComponent(handleManager, networkIDManager, connectionSystem.getRakNetInstance());
	networkObjectPtr->init(&handleManager, networkComponentHandle);
	networkObjectPtr->setNetworkID(networkID);
	networkSystem.registerActor(handleManager, networkObjectPtr);
	return ret;
}