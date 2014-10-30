#include "managerregister.h"

ManagerRegister::ManagerRegister() {
	container.resize(NUM_MANAGER_TYPES);
}

void ManagerRegister::add(void* manager, ManagerType type) {
	container[type] = manager;
}

void* ManagerRegister::get(ManagerType type) {
	return container[type];
}