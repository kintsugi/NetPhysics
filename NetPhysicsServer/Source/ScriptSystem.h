#ifndef SCRIPT_SYSTEM_H_INCLUDED
#define SCRIPT_SYSTEM_H_INCLUDED

#include "System.h"
#include "ComponentList.h"

namespace NetPhysics {
	class ScriptSystem : public System {
	public:

		ScriptSystem();

		void update(Register &engineRegister,
					const double dt);

	private:

		ComponentList componentList;
	};
}

#endif /* SCRIPT_SYSTEM_H_INCLUDED */