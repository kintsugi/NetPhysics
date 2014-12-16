#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef SYSTEM_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

namespace NetPhysics {
	class Register;

	enum UpdateMode {
		NO_PARAMETERS,
		DELTA_TIME,
		REGISTER,
		BOTH,
	};

	class System {
	public:

		System() : mode(NO_PARAMETERS) {}
		System(UpdateMode newMode) : mode(newMode) {}

		void virtual init() {}
		void virtual update() {}
		void virtual update(Register &reg, const double dt) {}
		void virtual update(Register &reg) {}
		void virtual update(const double dt) {}

		UpdateMode mode;
	};
}

#endif /* SYSTEM_H_INCLUDED */