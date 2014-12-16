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
#include "GameObjectList.h"

using namespace NetPhysics;

ClientSystem::ClientSystem() 
	: System(REGISTER)
	, componentList(CLIENT_COMPONENT)
{}

void ClientSystem::update(Register &reg) {
	HandleManager* handleManager = reg.getHandleManager();
	GameObjectManager* gameObjectManager = reg.getGameObjectManager();
	RakNet::RakPeerInterface* rakPeerInstance = reg.getRakPeerInstance();

	//Poll the connection state of the client, if it not a secure connection, destroy it.
	GameObjectList gameObjectList = gameObjectManager->getGameObjectsWithComponents(componentList);
	GameObject* gameObject;
	ClientComponent* clientComponent;
	for (gameObject = gameObjectList.next(); gameObject; gameObject = gameObjectList.next()) {
		clientComponent = gameObject->getComponent<ClientComponent>(*handleManager, CLIENT_COMPONENT);
		if (clientComponent) {
			RakNet::ConnectionState ret = rakPeerInstance->GetConnectionState(clientComponent->getClientGUID());
			if (ret == RakNet::ConnectionState::IS_DISCONNECTED ||
				ret == RakNet::ConnectionState::IS_DISCONNECTING ||
				ret == RakNet::ConnectionState::IS_NOT_CONNECTED ||
				ret == RakNet::ConnectionState::IS_SILENTLY_DISCONNECTING) {
				gameObject->destroy(*handleManager);
			}
		}
	}
}

void ClientSystem::initializeClient(Register &reg,
	RakNet::RakNetGUID guid)
{
	//Set up managers from the register.
	HandleManager* handleManager = reg.getHandleManager();
	GameObjectManager* gameObjectManager = reg.getGameObjectManager();
	ComponentManager* clientComponentManager = reg.getComponentManager(CLIENT_COMPONENT);
	ComponentManager* platerStateComponentManager = reg.getComponentManager(PLAYER_STATE_COMPONENT);
	RakNet::RakPeerInterface *rakPeerInstance = reg.getRakPeerInstance();

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

void ClientSystem::removeClient(Register &reg,
	NetworkKey networkKey)
{
	//Set up managers from the register.
	HandleManager* handleManager = reg.getHandleManager();
	GameObjectManager* gameObjectManager = reg.getGameObjectManager();
	NetworkHandleManager* networkHandleManager = reg.getNetworkHandleManager();

	//Retrieve the base component class from the networkIDManager (NetworkComponent functionality not needed)
	NetworkComponent* networkComponent = networkHandleManager->get<NetworkComponent>(networkKey);
	//Get the parent GameObject
	GameObject* gameObject = (GameObject*)handleManager->get(networkComponent->getOwner());
	//Remove
	gameObject->destroy(*handleManager);
}
