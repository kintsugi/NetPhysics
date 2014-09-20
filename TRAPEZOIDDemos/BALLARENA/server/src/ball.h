#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "btBulletDynamicsCommon.h"
#include "networkcomponent.h"

class NetworkComponent;
class worldObjectComponent;

/*
	Ball entity class. See Ball::update() for specifications.
*/
class Ball {
public:
	Ball(NetworkComponent* netComp, worldObjectComponent* obj) : connection(netComp), ballObject(obj), x(0), y(0), z(0), forceMultiplier(5), netForce(0, 0, 0), isDead(false){}
	void update();
	NetworkComponent* connection;
	worldObjectComponent* ballObject;

	float getX() {return x;}
	float getY() { return y; }
	float getZ() { return z; }
	void checkIfDead();
private:
	bool isDead;
	float x, y, z;
	float forceMultiplier;
	btVector3 netForce;
	/*
	Checks whether the position should update
	@param oldNum the old number
	@param newNum the new number
	@param percentChange the minimum percentage change between the two in order to return true
	@return if the percentage change is greater than the percentChange param will return true.
	Otherwise return false
	*/
	bool updateCheck(float, float, float);
	void send();
};

#endif