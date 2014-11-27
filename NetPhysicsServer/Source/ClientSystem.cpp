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

//For checking the connection state of a client
#include "RakPeerInterface.h"
#include "TimerComponent.h"

using namespace NetPhysics;

ClientSystem::ClientSystem() : System(REGISTER), filter(CLIENT_COMPONENT) {}

void ClientSystem::update(Register &engineRegister) {
	HandleManager* handleManager = engineRegister.getHandleManager();
	GameObjectManager* gameObjectManager = engineRegister.getGameObjectManager();
	RakNet::RakPeerInterface *rakPeerInstance = engineRegister.getRakPeerInstance();

	//Poll the connection state of the client, if it not a secure connection, destroy it.
	std::vector<GameObject*> gameObjects = gameObjectManager->getGameObjects(filter);
	ClientComponent* clientComponent;
	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {
		clientComponent = (*iter)->getComponent<ClientComponent>(*handleManager, CLIENT_COMPONENT);
		if (clientComponent) {
			RakNet::ConnectionState ret = rakPeerInstance->GetConnectionState(clientComponent->getClientGUID());
			if (ret == RakNet::ConnectionState::IS_DISCONNECTED ||
				ret == RakNet::ConnectionState::IS_DISCONNECTING ||
				ret == RakNet::ConnectionState::IS_NOT_CONNECTED ||
				ret == RakNet::ConnectionState::IS_SILENTLY_DISCONNECTING) {
				(*iter)->destroy(*handleManager);
			}
		}
	}
}

void ClientSystem::initializeClient(Register &engineRegister,
									RakNet::RakNetGUID guid) {
	//Set up managers from the register.
	HandleManager* handleManager = engineRegister.getHandleManager();
	GameObjectManager* gameObjectManager = engineRegister.getGameObjectManager();
	ComponentManager* clientComponentManager = engineRegister.getComponentManager(CLIENT_COMPONENT);
	ComponentManager* platerStateComponentManager = engineRegister.getComponentManager(PLAYER_STATE_COMPONENT);
	RakNet::RakPeerInterface *rakPeerInstance = engineRegister.getRakPeerInstance();

	//Create a new game object for the client.
	GameObject* clientGameObject = new GameObject(*handleManager);
	gameObjectManager->createGameObject(clientGameObject);

	//Add a ClientComponent & PlayerStateComponent.
	ClientComponent* newClientComponent = new ClientComponent(*handleManager, rakPeerInstance, guid);
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
