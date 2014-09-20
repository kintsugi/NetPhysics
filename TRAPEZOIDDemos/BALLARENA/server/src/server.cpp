#include "server.h"
#include <memory>
#include "BitStream.h"
#include "networkcomponent.h"

Server::Server(int port) : serverPort(port), maxClients(20) {
	//Get instance of RakNet
	peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd(serverPort, 0);
	//Start server with maximum connections of maxClients
	RakNet::StartupResult r = peer->Startup(maxClients, &sd, 1);
	if (r != RakNet::StartupResult::RAKNET_STARTED)
		std::cout << std::endl << "Server failed to start. Result code: " << r;
	else {
		std::cout << std::endl << "Server started successfully.";
		peer->SetMaximumIncomingConnections(maxClients);
	}
	//Start the server clock
	currentTime = RakNet::GetTimeUS();
	lastTime = currentTime;
}

void Server::update() {
	//Calculate the dt between last server tick
	//TODO calculate server fps
	RakNet::Packet *packet;
	lastTime = currentTime;
	currentTime = RakNet::GetTimeUS();
	double dt = ((double)currentTime - lastTime)/1000000.0f;
	//Handle incoming packets
	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		packetHandler(packet);
	for (std::vector<Ball>::iterator iter = players.begin(); iter != players.end(); iter++) {
		iter->update();
	}
	gameWorld.update((float)dt);
}

void Server::packetHandler(RakNet::Packet *packet) {

	switch (packet->data[0]) {
		case ID_NEW_INCOMING_CONNECTION:
			std::cout << std::endl << "A client has connected. System Address: '" << packet->systemAddress.ToString() << "'";
			createBallEntity(packet->guid); break;
		case ID_DISCONNECTION_NOTIFICATION:
			deleteBallEntity(packet->guid);
			break;
		case NETWORK_COMPONENT_MESSAGE:	
			updateNetworkComponent(packet);
			break;
	}
}

void Server::createBallEntity(RakNet::RakNetGUID guid) {
	//Create the WorldObjectComponent for the new ball
	physicsObject obj;
	//bullet physics type
	std::unique_ptr<btCollisionShape> ball(new btSphereShape(1));
	std::unique_ptr<btDefaultMotionState> ballMotionState(
		new btDefaultMotionState(
		btTransform(btQuaternion(0, 0, 0, 1),
		btVector3(0, 0, 0))));	//Creates at (0,0,0)
	std::unique_ptr<btScalar> mass(new btScalar(1));
	btVector3 localInertia(0, 0, 0);
	ball.get()->calculateLocalInertia(*mass.get(), localInertia);
	std::unique_ptr<btVector3> localInertiaPtr(new btVector3(localInertia));
	//move the memory into obj.
	obj.collisionShape = std::move(ball);
	obj.motionState = std::move(ballMotionState);
	obj.localInertia = std::move(localInertiaPtr);
	obj.mass = std::move(mass);
	//Create the Ball enity with obj and creating a NetworkComponent
	players.push_back(Ball(new NetworkComponent(peer, &networkIDManager, guid), gameWorld.createWorldObject(obj)));
	Ball newBall = players.back();
	//Bitstream to send to client to create the player controlled ball.
	//TODO: broadcast to other clients that an enemy ball has been created
	RakNet::BitStream notifyClient;
	//Message ID, network component network id.
	notifyClient.Write((RakNet::MessageID)CREATE_PLAYER_BALL);
	newBall.connection->GetNetworkID();
	RakNet::NetworkID networkID = newBall.connection->GetNetworkID();
	notifyClient.Write(networkID);
	//Radius, X, Y, Z
	notifyClient.Write(1.0f); notifyClient.Write(0.0f); notifyClient.Write(0.0f); notifyClient.Write(0.0f);
	//Send to connecting client to create a player ball
	peer->Send(&notifyClient, HIGH_PRIORITY, RELIABLE_ORDERED, 0, guid, false);
	//Send to connecting player to create an Enemy Ball for every player currently connected
	for (std::vector<Ball>::iterator iter = players.begin(); iter != players.end(); iter++) {
		if (iter->connection->getGUID() != guid) {
			RakNet::BitStream enemyBallData;
			enemyBallData.Write((RakNet::MessageID)CREATE_ENEMY_BALL);
			enemyBallData.Write(iter->connection->GetNetworkID());
			enemyBallData.Write(1.0f);
			enemyBallData.Write(iter->getX());
			enemyBallData.Write(iter->getY());
			enemyBallData.Write(iter->getZ());
			peer->Send(&enemyBallData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, guid, false);
		}
		
	}
	//Now broadcast to all other players to make an enemy ball of the same attributes.
	RakNet::BitStream notifyOtherClients;
	//Message ID, network component network id.
	notifyOtherClients.Write((RakNet::MessageID)CREATE_ENEMY_BALL);
	notifyOtherClients.Write(networkID);
	//Radius, X, Y, Z
	notifyOtherClients.Write(1.0f); notifyOtherClients.Write(0.0f); notifyOtherClients.Write(0.0f); notifyOtherClients.Write(0.0f);
	//Broadcast
	peer->Send(&notifyOtherClients, HIGH_PRIORITY, RELIABLE_ORDERED, 0, guid, true);
}

void Server::deleteBallEntity(RakNet::RakNetGUID guid) {
	for (std::vector<Ball>::iterator iter = players.begin(); iter != players.end();) {
		if (iter->connection->getGUID() == guid) {
			//Tell Clients the ball is deleted.
			RakNet::BitStream deletedBall;
			deletedBall.Write((RakNet::MessageID)DELETE_ENEMY_BALL);
			deletedBall.Write(iter->connection->GetNetworkID());
			peer->Send(&deletedBall, HIGH_PRIORITY, RELIABLE_ORDERED, 0, guid, true);
			delete iter->connection;	//TODO Write a better network component handler so deletion does not have to be done manually
			iter = players.erase(iter++);
		} else
			++iter;
	}
}

//WARNING: C# client and server interactions untested
void Server::updateNetworkComponent(RakNet::Packet *packet) {
	RakNet::NetworkID networkComponentNetworkID;
	//get the guid of the client
	RakNet::RakNetGUID componentGUID = packet->guid;
	//Create the bitstream
	RakNet::BitStream in(packet->data, packet->length, false);
	//Skip the messageID
	in.IgnoreBytes(sizeof(RakNet::MessageID));
	//Read the networkComponent ID
	//TODO test this since client sends it as a C# ulong not as a NetworkObjectID
	in.Read(networkComponentNetworkID);
	//Find the corresponding NetworkComponent and update the in bitstream
	NetworkComponent* netcomp = networkIDManager.GET_OBJECT_FROM_ID<NetworkComponent*>(networkComponentNetworkID);
	if (netcomp->getGUID().operator==(componentGUID)) {
		std::unique_ptr<RakNet::BitStream> newIn(new RakNet::BitStream(packet->data, packet->length, true));
		netcomp->in = std::move(newIn);
	}
}