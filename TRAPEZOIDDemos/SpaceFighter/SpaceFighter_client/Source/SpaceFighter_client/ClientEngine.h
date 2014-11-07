#pragma once

#include "XLib.h"
#include "EngineRegister.h"
#include "HandleManager.h"

class ClientEngine {
public:
	ClientEngine();

	void update(float dt);

	void init();

private:

	bool readyForPostInit;
	
	//Initialization
	void initManagers();
	void initSystems();

	//Managers
	HandleManager handleManager;

};