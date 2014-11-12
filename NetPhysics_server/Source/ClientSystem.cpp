#include "ClientSystem.h"
#include "EngineRegister.h"
#include "HandleManager.h"
#include "GameObjectManager.h"
#include "ClientComponent.h"
#include "PlayerStateComponent.h"
#include "ComponentManager.h"
#include "Component.h"
#include "NetworkComponent.h"

ClientSystem::ClientSystem() : filter(CLIENT_COMPONENT_HANDLE) {}

void ClientSystem::initializeClient(EngineRegister &engineRegister,
									RakNet::RakNetGUID guid)
{
	//Set up managers from the register.
	HandleManager* handleManager = engineRegister.getHandleManager();
	GameObjectManager* gameObjectManager = engineRegister.getGameObjectManager();
	ComponentManager* clientComponentManager = engineRegister.getComponentManager(CLIENT_COMPONENT);
	ComponentManager* platerStateComponentManager = engineRegister.getComponentManager(PLAYER_STATE_COMPONENT);
	RakNet::RakPeerInterface *RakPeerInstance = engineRegister.getRakPeerInstance();

	//Create a new game object for the client.
	GameObject* clientGameObject = gameObjectManager->createGameObject(*handleManager);

	//Add a ClientComponent & PlayerStateComponent.
	ClientComponent* newClientComponent = new ClientComponent(*handleManager, RakPeerInstance, guid);
	PlayerStateComponent* newPlayerStateComponent = new PlayerStateComponent(*handleManager, UNINITIALIZED);

	Handle clientComponentHandle = clientComponentManager->createComponent(newClientComponent);
	Handle playerStateComponent = platerStateComponentManager->createComponent(newPlayerStateComponent);

	clientGameObject->addComponent(*handleManager, clientComponentHandle);
	clientGameObject->addComponent(*handleManager, playerStateComponent);
}

void ClientSystem::removeClient(EngineRegister &engineRegister, NetworkKey networkKey) {
	//Set up managers from the register.
	HandleManager* handleManager = engineRegister.getHandleManager();
	GameObjectManager* gameObjectManager = engineRegister.getGameObjectManager();
	NetworkHandleManager* networkHandleManager = engineRegister.getNetworkHandleManager();

	//Retrieve the base component class from the networkIDManager (NetworkComponent functionality not needed)
	NetworkComponent* networkComponent = networkHandleManager->get<NetworkComponent>(networkKey);
	//Get the parent GameObject
	GameObject* gameObject = (GameObject*)handleManager->get(networkComponent->getParent());
	//Remove
	gameObject->removeSelf(*handleManager);
}
