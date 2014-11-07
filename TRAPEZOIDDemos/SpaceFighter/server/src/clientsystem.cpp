#include "clientsystem.h"
#include "engineRegister.h"
#include "NetworkIDManager.h"
#include "gameobjectmanager.h"
#include "clientmanager.h"
#include "playerstatemanager.h"
#include "networkcomponent.h"
#include "component.h"

ClientSystem::ClientSystem() : filter(CLIENT_COMPONENT) {}

void ClientSystem::initializeClient(EngineRegister &engineRegister,
									RakNet::RakNetGUID guid)
{
	//Set up managers from the register.
	HandleManager* handleManager = engineRegister.getManager<HandleManager>(HANDLE_MANAGER);
	GameObjectManager* gameObjectManager = engineRegister.getManager<GameObjectManager>(GAME_OBJECT_MANAGER);
	ClientManager* clientManager = engineRegister.getManager<ClientManager>(CLIENT_MANAGER);
	PlayerStateManager* playerStateManager = engineRegister.getManager<PlayerStateManager>(PLAYER_STATE_MANAGER);

	//Create a new game object for the client.
	GameObject* clientGameObject = gameObjectManager->createGameObject(*handleManager);
	//Add a ClientComponent & PlayerStateComponent.
	clientGameObject->addComponent(*handleManager, clientManager->createComponent(*handleManager, engineRegister.getRakPeerInstance(), guid));
	clientGameObject->addComponent(*handleManager, playerStateManager->createComponent(*handleManager, UNINITIALIZED));
}

void ClientSystem::removeClient(EngineRegister &engineRegister, NetworkKey networkKey) {
	//Set up managers from the register.
	HandleManager* handleManager = engineRegister.getManager<HandleManager>(HANDLE_MANAGER);
	GameObjectManager* gameObjectManager = engineRegister.getManager<GameObjectManager>(GAME_OBJECT_MANAGER);
	NetworkHandleManager* networkHandleManager = engineRegister.getManager<NetworkHandleManager>(NETWORK_HANDLE_MANAGER);

	//Retrieve the base component class from the networkIDManager (NetworkComponent functionality not needed)
	NetworkComponent* networkComponent = networkHandleManager->get<NetworkComponent>(networkKey);
	//Get the parent GameObject
	GameObject* gameObject = (GameObject*)handleManager->get(networkComponent->getParent());
	//Remove
	gameObject->removeSelf(*handleManager);
}
