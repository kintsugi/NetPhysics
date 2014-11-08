#include "SpaceFighter_client.h"
#include "SpaceFighterEngine.h"

ASpaceFighterEngine::ASpaceFighterEngine(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP) {
	PrimaryActorTick.bCanEverTick = true;
	postInitReady = false;
}

/*
void ASpaceFighterEngine::BeginPlay() {
	Super::BeginPlay();
	init();
}

void ASpaceFighterEngine::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	if (clientController)
		clientController->disconnect();
}

void ASpaceFighterEngine::Tick(float dt) {
	Super::Tick(dt);
	updateManagers(dt);
	updateSystems(dt);
}

void ASpaceFighterEngine::init() {
	connectionSystem.connect();
	engineRegister.init(connectionSystem.getRakNetInstance());
	postInitReady = true;
	initManagers();
	initSystems();
}

void ASpaceFighterEngine::initManagers() {
	if (postInitReady) {
		engineRegister.addManager(&handleManager, HANDLE_MANAGER);
		engineRegister.addManager(&networkManager, NETWORK_MANAGER);
		engineRegister.addManager(&networkHandleManager, NETWORK_HANDLE_MANAGER);
	}
}

void ASpaceFighterEngine::initSystems() {
	if (postInitReady) {
		engineRegister.addSystem(&connectionSystem, CONNECTION_SYSTEM);
		engineRegister.addSystem(&networkSystem, NETWORK_SYSTEM);
	}
}

void ASpaceFighterEngine::updateManagers(double dt) {
	networkManager.update(handleManager);
}

void ASpaceFighterEngine::updateSystems(double dt) {
	connectionSystem.update();
	handlePackets(connectionSystem.getPackets());
}

void ASpaceFighterEngine::handlePackets(TArray<PacketToBitStream> packets) {
	for (auto iter = packets.CreateIterator(); iter; iter++) {
		switch (iter->messageID) {
			case NetworkMessage::ID::NETWORK_COMPONENT_MESSAGE: {
				networkSystem.sendToNetworkComponent(networkHandleManager, handleManager, *iter);
				break;
			}
			case NetworkMessage::ID::CLIENT_INIT: {
				if (!clientController)
					clientController = initClientController(*iter);
				break;
			}
		}
	}
}

AClientController* ASpaceFighterEngine::initClientController(PacketToBitStream packet) {
	packet.bitStream->IgnoreBytes(sizeof(RakNet::MessageID));
	RakNet::NetworkID networkID;
	packet.bitStream->Read(networkID);
	AClientController *newClientController = spawnNetworkActor<AClientController>(networkID);
	newClientController->setServerGUID(packet.guid);
	return newClientController;
}*/