#ifndef SCRIPT_SYSTEM_H_INCLUDED
#define SCRIPT_SYSTEM_H_INCLUDED

#include "System.h"
#include "GameObjectFilter.h"

class ScriptSystem : public System {
public:

	ScriptSystem();

	void update(Register *engineRegister, 
				const double dt);

private:
	GameObjectFilter filter;
};

#endif /* SCRIPT_SYSTEM_H_INCLUDED */