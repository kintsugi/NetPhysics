#ifndef MANAGER_REGISTER_H
#define MANAGER_REGISTER_H

#include <vector>
#include "RakPeerInterface.h"

enum ManagerType {
	HANDLE_MANAGER,
	NETWORK_ID_MANAGER,
	GAME_OBJECT_MANAGER,
	PHYSICS_MANAGER,
	NETWORK_MANAGER,
	CLIENT_MANAGER,
	PLAYER_STATE_MANAGER,
	TIMER_MANAGER,
	NUM_MANAGER_TYPES,
};

class ManagerRegister {
public:

	ManagerRegister();

	void add(void* manager, ManagerType type);

	void* get(ManagerType type);

	template <class T>
	T* get(ManagerType type);

	RakNet::RakPeerInterface* peer;

private:
	std::vector<void*> container;
};

template <class T>
T* ManagerRegister::get(ManagerType type) {
	return (T*)container[type];
}

#endif