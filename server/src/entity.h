#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "networkcomponent.h"
#include <iostream>

//still testing
class Entity {
public:
	Entity(NetworkComponent* netComp): net(netComp) {
		
	}
	void update() {
		net->Update(this);
	}
	void static test(void* obj) {
		Entity *test1 = &*(Entity*)obj;
		test1->x = 5;
	}
	int x;
private:
	NetworkComponent *net;
};

#endif