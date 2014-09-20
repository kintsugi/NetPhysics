#include "ball.h"
#include "BitStream.h"
#include "btBulletDynamicsCommon.h"
#include "world.h"
#include "messages.h"
#include "RakPeerInterface.h"
#include "networkcomponent.h"
#include <cmath>
#include <iostream>

void Ball::update() {
	if (isDead)
		return;
	btTransform trans; float newX, newY, newZ; 
	//Get the rigidbody from the simulation
	btRigidBody* ball = ballObject->getRigidBody();
	//Process inbound data (or updates that only happen when a new message is received)
	if (connection->in.get() != nullptr) {
		float directionX, directionY, directionZ, vertical;
		//Ignore 9 bytes which is the size in bytes of the casted Message type to a byte + sizeof(ulong) on C# client
		connection->in->IgnoreBytes(sizeof(RakNet::MessageID) + sizeof(RakNet::NetworkID));
		//Read data from bitstream.
		connection->in->Read(directionX);
		connection->in->Read(directionY);
		connection->in->Read(directionZ);
		//Button input axes.
		connection->in->Read(vertical);
		//Create a normalized vector of the rotation angles.
		btVector3 direction(directionX, directionY, directionZ);
		if (directionX != 0 || directionY != 0 || directionZ != 0)
			direction = direction.normalize();
		//Update net force
		netForce = btVector3(direction.getX(), direction.getY(), direction.getZ()) * vertical * forceMultiplier;
		//std::cout << std::endl << "(" << horizontal << ", " << vertical << ")";
		//std::cout << std::endl << "(" << directionX << ", " << directionY <<  ", " << directionZ << ")";
		//std::cout << std::endl << "(" << netForce.getX() << ", " << netForce.getY() << ", " << netForce.getZ() << ")";
		connection->in.release();
	}
	//Process Object updates (updates that need to happen every frame)
	ball->applyCentralForce(netForce);
	//Process outbound data (Whenever something needs to be sent)
	ball->getMotionState()->getWorldTransform(trans);
	newX = (float)trans.getOrigin().getX(); newY = (float)trans.getOrigin().getY(); newZ = (float)trans.getOrigin().getZ();
	//Send the position only if the position has changed by at least 0.001 units in any direction, but use percent difference if the difference is more than 0.1
	if (abs(newX - x) > 0.001 || abs(newY - y) > 0.001 || abs(newZ - z) > 0.001) {
		x = newX; y = newY; z = newZ;
		//std::cout << std::endl << "(" << x << ", " << y << ", " << z << ")";
		if (abs(newX - x) > 0.1 || abs(newY - y) > 0.1 || abs(newZ - z) > 0.1) {
			if (updateCheck(x, newX, 0.01) || updateCheck(y, newY, 0.01) || updateCheck(z, newZ, 0.01))
				send();
		} else
			send();
	}
	checkIfDead();
}

void Ball::checkIfDead() {
	//Area is 25x25x25 and players are 1m in radius
	if (x > 24 || x < -24 || y > 24 || y < -24 || z > 24 || z < -24) {
		isDead = true;
		ballObject->getWorld()->removeRigidBody(ballObject->getRigidBody());
		//Broadcast to other players to delete the enemy ball.
		RakNet::BitStream out;
		out.Write((RakNet::MessageID)DELETE_ENEMY_BALL); out.Write(connection->GetNetworkID());
		connection->getRakNetInstance()->Send(&out, HIGH_PRIORITY, RELIABLE_ORDERED, 0, connection->getGUID(), true);
		RakNet::BitStream youLost;
		youLost.Write((RakNet::MessageID)YOU_LOST);
		connection->getRakNetInstance()->Send(&youLost, HIGH_PRIORITY, RELIABLE_ORDERED, 0, connection->getGUID(), false);
	}
}

bool Ball::updateCheck(float oldNum, float newNum, float percentChange) {
	if (oldNum == 0 && newNum != 0)
		return true;
	else if (abs((newNum - oldNum) / oldNum) > percentChange) {
		return true;
	}
	return false;
}

void Ball::send() {
	//std::cout << std::endl << "sending";
	RakNet::BitStream out;
	//Message, networkID
	out.Write((RakNet::MessageID)NETWORK_COMPONENT_MESSAGE); out.Write(connection->GetNetworkID());
	//x, y, z;
	out.Write(x); out.Write(y); out.Write(z);
	//Broadcast
	connection->getRakNetInstance()->Send(&out, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
}