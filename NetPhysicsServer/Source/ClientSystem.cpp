#include "ClientSystem.h"

//Register includes
#include "Register.h"
#include "HandleManager.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"

//Component includes
#include "ClientComponent.h"
#include "PlayerStateComponent.h"
#include "NetworkComponent.h"

ClientSystem::ClientSystem() : filter(CLIENT) {}

void ClientSystem::initializeClient(Register &engineRegister,
									RakNet::RakNetGUID guid) {
	//Set up managers from the register.
	HandleManager* handleManager = engineRegister.getHandleManager();
	GameObjectManager* gameObjectManager = engineRegister.getGameObjectManager();
	ComponentManager* clientComponentManager = engineRegister.getComponentManager(CLIENT);
	ComponentManager* platerStateComponentManager = engineRegister.getComponentManager(PLAYER_STATE);
	RakNet::RakPeerInterface *RakPeerInstance = engineRegister.getRakPeerInstance();

	//Create a new game object for the client.
	GameObject* clientGameObject = new GameObject(*handleManager);
	gameObjectManager->createGameObject(clientGameObject);

	//Add a ClientComponent & PlayerStateComponent.
	ClientComponent* newClientComponent = new ClientComponent(*handleManager, RakPeerInstance, guid);
	PlayerStateComponent* newPlayerStateComponent = new PlayerStateComponent(*handleManager, UNINITIALIZED);
	ComponentHandle clientComponentHandle = clientComponentManager->createComponent(newClientComponent);
	ComponentHandle playerStateComponent = platerStateComponentManager->createComponent(newPlayerStateComponent);
	clientGameObject->addComponent(*handleManager, clientComponentHandle);
	clientGameObject->addComponent(*handleManager, playerStateComponent);
}

void ClientSystem::removeClient(Register &engineRegister,
								NetworkKey networkKey) {
	//Set up managers from the register.
	HandleManager* handleManager = engineRegister.getHandleManager();
	GameObjectManager* gameObjectManager = engineRegister.getGameObjectManager();
	NetworkHandleManager* networkHandleManager = engineRegister.getNetworkHandleManager();

	//Retrieve the base component class from the networkIDManager (NetworkComponent functionality not needed)
	NetworkComponent* networkComponent = networkHandleManager->get<NetworkComponent>(networkKey);
	//Get the parent GameObject
	GameObject* gameObject = (GameObject*)handleManager->get(networkComponent->getOwner());
	//Remove
	gameObject->destroy(*handleManager);
}
