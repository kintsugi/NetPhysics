#include "playerinitsystem.h"
#include <vector>
#include "engineregister.h"
#include "handlemanager.h"
#include "gameobjectmanager.h"
#include "networkmanager.h"
#include "gameobject.h"
#include "playerstatecomponent.h"
#include "clientcomponent.h"
#include "networkmessage.h"
#include "NetworkIDManager.h"

PlayerInitSystem::PlayerInitSystem() {
	playerInitFilter.addToFilter(PLAYER_STATE_COMPONENT_HANDLE);
	playerInitFilter.addToFilter(CLIENT_COMPONENT_HANDLE);
}

void PlayerInitSystem::update(EngineRegister& engineRegister) {
	//Set up managers from the register
	HandleManager *handleManager = engineRegister.getManager<HandleManager>(HANDLE_MANAGER);
	GameObjectManager *gameObjectManager = engineRegister.getManager<GameObjectManager>(GAME_OBJECT_MANAGER);
	RakNet::RakPeerInterface* peer = engineRegister.getRakPeerInstance();

	//Look for uninitialized players.
	XLib::Vector<GameObject*> gameObjects = gameObjectManager->getGameObjects(playerInitFilter);
	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {
		//Get the PlayerState component
		PlayerStateComponent *playerStateComponent = (*iter)->getComponent<PlayerStateComponent>(*handleManager, PLAYER_STATE_COMPONENT_HANDLE);
		//Check if the player has been initialized yet.
		if (playerStateComponent) {
			if (playerStateComponent->getState() == UNINITIALIZED) {
				init(engineRegister, *iter);
			}
		}
	}
}

void PlayerInitSystem::init(EngineRegister& engineRegister, GameObject* gameObject) {
	//set up managers from the register.
	HandleManager *handleManager = engineRegister.getManager<HandleManager>(HANDLE_MANAGER);
	NetworkManager *networkManager = engineRegister.getManager<NetworkManager>(NETWORK_MANAGER);
	NetworkHandleManager* networkHandleManager = engineRegister.getManager<NetworkHandleManager>(NETWORK_HANDLE_MANAGER);
	RakNet::RakPeerInterface* peer = engineRegister.getRakPeerInstance();

	//Add a NetworkComponent to the game object and notify the client.
	gameObject->addComponent(*handleManager, networkManager->createComponent(engineRegister, peer));

	//Get the NetworkComponent and ClientComponent to notify the client.
	NetworkComponent* networkComponent = gameObject->getComponent<NetworkComponent>(*handleManager, NETWORK_COMPONENT_HANDLE);


	ClientComponent* clientComponent = gameObject->getComponent<ClientComponent>(*handleManager, CLIENT_COMPONENT_HANDLE);
	PlayerStateComponent *playerStateComponent = gameObject->getComponent<PlayerStateComponent>(*handleManager, PLAYER_STATE_COMPONENT_HANDLE);

	//Get the guid and networkID to send the initClient message.
	RakNet::RakNetGUID clientGUID = clientComponent->getClientGUID();
	NetworkKey networkKey = networkComponent->getNetworkKey();

	//Create the MessageDetails to initialize the ClientController.
	NetworkMessage::Package package(peer, clientGUID);
	NetworkMessage::Send::clientInit(package, networkKey);
	playerStateComponent->setState(INITIALIZED);
}