#ifndef SCRIPT_COMPONENT_H_INCLUDED
#define SCRIPT_COMPONENT_H_INCLUDED

//Inherits Component
#include "Component.h"


namespace NetPhysics {
	class HandleManager;
	class Register;

	class ScriptComponent : public Component {
	public:

		ScriptComponent(
			HandleManager &handleManager,
			Register &engineRegister);
		~ScriptComponent();

		virtual void update(const double dt) = 0;
		virtual void start() {}
		virtual void destroy() {}

	protected:

		Register* engineRegister;
	};
}

#endif /* SCRIPT_COMPONENT_H_INCLUDED */