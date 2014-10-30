#include "clientsystem.h"
#include "managerregister.h"
#include "gameobjectmanager.h"
#include "clientmanager.h"
#include "playerstatemanager.h"

ClientSystem::ClientSystem() : filter(CLIENT_COMPONENT) {}

void ClientSystem::initializeClient(ManagerRegister &managerRegister,
									RakNet::RakPeerInterface* peer,
									RakNet::RakNetGUID guid)
{
	//Set up managers from the register.
	HandleManager* handleManager = managerRegister.get<HandleManager>(HANDLE_MANAGER);
	GameObjectManager* gameObjectManager = managerRegister.get<GameObjectManager>(GAME_OBJECT_MANAGER);
	ClientManager* clientManager = managerRegister.get<ClientManager>(CLIENT_MANAGER);
	PlayerStateManager* playerStateManager = managerRegister.get<PlayerStateManager>(PLAYER_STATE_MANAGER);

	//Create a new game object for the client.
	GameObject* clientGameObject = gameObjectManager->createGameObject(*handleManager);
	//Add a ClientComponent & PlayerStateComponent.
	clientGameObject->addComponent(clientManager->createComponent(*handleManager, peer, guid));
	clientGameObject->addComponent(playerStateManager->createComponent(*handleManager, UNINITIALIZED));
}