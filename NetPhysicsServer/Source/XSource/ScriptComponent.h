#ifndef SCRIPT_COMPONENT_H_INCLUDED
#define SCRIPT_COMPONENT_H_INCLUDED

//Inherits Component
#include "Component.h"
#include "ComponentList.h"


namespace NetPhysics {
	class HandleManager;
	class Register;
	class GameObject;

	class ScriptComponent : public Component {
	public:

		ScriptComponent(Register &reg);
		~ScriptComponent();

		virtual void update(const double dt) = 0;
		virtual void start() {}
		virtual void destroy() {}

	protected:

		Register* getRegister();
		GameObject* getGameObject();

	private:

		Register* reg;
	};
}

#endif /* SCRIPT_COMPONENT_H_INCLUDED */