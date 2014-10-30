#include "gamestatesystem.h"
#include <iostream>
#include <vector>
#include "managerregister.h"
#include "handlemanager.h"
#include "gameobjectmanager.h"
#include "networkmanager.h"
#include "gameobject.h"
#include "playerstatecomponent.h"
#include "clientcomponent.h"
#include "networkmessages.h"

GameStateSystem::GameStateSystem() {
	playerStateFilter.addToFilter(PLAYER_STATE_COMPONENT);
	playerStateFilter.addToFilter(CLIENT_COMPONENT);
}

void GameStateSystem::update(ManagerRegister& managerRegister) {
	//Set up managers from the register
	HandleManager *handleManager = managerRegister.get<HandleManager>(HANDLE_MANAGER);
	GameObjectManager *gameObjectManager = managerRegister.get<GameObjectManager>(GAME_OBJECT_MANAGER);

	//Look for uninitialized players.
	std::vector<GameObject*> gameObjects = gameObjectManager->getGameObjects(playerStateFilter);
	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {
		//Get the PlayerState component
		PlayerStateComponent *playerStateComponent = (*iter)->getComponent<PlayerStateComponent>(*handleManager, PLAYER_STATE_COMPONENT);
		//Check if the player has been initialized yet.
		if (playerStateComponent) {
			if (playerStateComponent->getState() == UNINITIALIZED) {
				initializePlayer(managerRegister, *iter);
			}
		}
	}
	//Test Code
	//Send a test string to all inited players
	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {
		//Get the PlayerState component
		PlayerStateComponent *playerState = (*iter)->getComponent<PlayerStateComponent>(*handleManager, PLAYER_STATE_COMPONENT);
		if (playerState) {
			if (playerState->getState() == INITIALIZED) {
				NetworkComponent* networkComponent = (*iter)->getComponent<NetworkComponent>(*handleManager, NETWORK_COMPONENT);
				ClientComponent* clientComponent = (*iter)->getComponent<ClientComponent>(*handleManager, CLIENT_COMPONENT);
				RakNet::RakNetGUID clientGUID = clientComponent->getClientGUID();
				RakNet::NetworkID networkID = networkComponent->GetNetworkID();
				RakNet::BitStream bsOut;
				bsOut.Write((RakNet::MessageID)NETWORK_COMPONENT_MESSAGE);
				bsOut.Write(networkID);
				bsOut.Write("Hello World");
				managerRegister.peer->Send(&bsOut, PacketPriority::HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientGUID, false);
			}
		}
	}

}

void GameStateSystem::initializePlayer(ManagerRegister& managerRegister, GameObject* gameObject) {
	//set up managers from the register.
	HandleManager *handleManager = managerRegister.get<HandleManager>(HANDLE_MANAGER);
	NetworkManager *networkManager = managerRegister.get<NetworkManager>(NETWORK_MANAGER);
	RakNet::NetworkIDManager *networkIDManager = managerRegister.get<RakNet::NetworkIDManager>(NETWORK_ID_MANAGER);

	//Add a NetworkComponent to the game object and notify the client.
	gameObject->addComponent(networkManager->createComponent(*handleManager, *networkIDManager, managerRegister.peer));

	//Get the NetworkComponent and ClientComponent to notify the client.
	NetworkComponent* networkComponent = gameObject->getComponent<NetworkComponent>(*handleManager, NETWORK_COMPONENT);
	ClientComponent* clientComponent = gameObject->getComponent<ClientComponent>(*handleManager, CLIENT_COMPONENT);
	PlayerStateComponent *playerStateComponent = gameObject->getComponent<PlayerStateComponent>(*handleManager, PLAYER_STATE_COMPONENT);

	//Get the guid and networkID to construct the bitstream.
	RakNet::RakNetGUID clientGUID = clientComponent->getClientGUID();
	RakNet::NetworkID networkID = networkComponent->GetNetworkID();

	//Write a START_PLAYER message
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)START_PLAYER);
	bsOut.Write(networkID);
	//Send and set the state to initialized
	managerRegister.peer->Send(&bsOut, PacketPriority::HIGH_PRIORITY, RELIABLE_ORDERED, 0, clientGUID, false);
	playerStateComponent->setState(INITIALIZED);
}