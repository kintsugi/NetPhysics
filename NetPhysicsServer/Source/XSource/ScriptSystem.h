#ifndef SCRIPT_SYSTEM_H_INCLUDED
#define SCRIPT_SYSTEM_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef SCRIPT_SYSTEM_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

#include "System.h"
#include "ComponentList.h"

namespace NetPhysics {
	class ScriptSystem : public System {
	public:

		ScriptSystem();

		void update(Register &reg,
					const double dt);

	private:

		ComponentList componentList;
	};
}

#endif /* SCRIPT_SYSTEM_H_INCLUDED */