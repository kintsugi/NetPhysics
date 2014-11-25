#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#ifdef CLIENT
	#undef SYSTEM_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* CLIENT */

enum UpdateMode {
	NO_PARAMETERS,
	DELTA_TIME,
	REGISTER,
	BOTH,
};

class Register;

class System {
public:

	System() : mode(NO_PARAMETERS) {}
	System(UpdateMode newMode) : mode(newMode) {}

	void virtual init() {}
	void virtual update() {}
	void virtual update(Register *engineRegister,
						const double dt) {}
	void virtual update(Register *engineRegister) {}
	void virtual update(const double dt) {}

	UpdateMode mode;
};

#endif /* SYSTEM_H_INCLUDED */