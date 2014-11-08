

#pragma once
#include "SpaceFighter_client.h"




/*//Engine function includes
#include "EngineRegister.h"

//Managers
#include "AllowWindowsPlatformTypes.h"
#include "NetworkHandleManager.h"
#include "HideWindowsPlatformTypes.h"
#include "HandleManager.h"
#include "NetworkManager.h"



//Systems
#include "ConnectionSystem.h"
#include "NetworkSystem.h"
#include "NetworkObject.h"
*/

#include "XLib.h"
#include "GameFramework/Actor.h"
#include "SpaceFighterEngine.generated.h"

//class AClientController;

UCLASS()
class ASpaceFighterEngine : public AGameMode
{
	GENERATED_UCLASS_BODY()
public:
	//virtual void BeginPlay() override;
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//virtual void Tick(float dt) override;
	
	//Engine Register
	//EngineRegister engineRegister;

	//Client Controller
	//AClientController* clientController;

	//Managers
	//HandleManager handleManager;
	//NetworkManager networkManager;
	//NetworkHandleManager networkHandleManager;

	//Systems
	//ConnectionSystem connectionSystem;
	//NetworkSystem networkSystem;

	//init function
	void init();
	void initManagers();
	void initSystems();
	//Managers must be updated before systems
	void updateManagers(double dt);
	void updateSystems(double dt);

	//Utility functions
	//void handlePackets(TArray<PacketToBitStream> packets);
	//AClientController* initClientController(PacketToBitStream packet);

	//template <class T>
	//T* spawnNetworkActor(NetworkKey networkID);

	//False if the engine is not ready to start
	bool postInitReady;
	
};

/*template <class T>
T* ASpaceFighterEngine::spawnNetworkActor(NetworkKey networkKey) {
	T* ret = (T*)GetWorld()->SpawnActor(T::StaticClass());
	NetworkObject* networkObjectPtr = (NetworkObject*)ret;
	Handle networkComponentHandle = networkManager.createComponent(handleManager, networkHandleManager, connectionSystem.getRakNetInstance());
	networkObjectPtr->init(&handleManager, networkComponentHandle);
	networkObjectPtr->setNetworkKey(networkKey);
	networkSystem.registerActor(handleManager, networkObjectPtr);
	return ret;
}*/