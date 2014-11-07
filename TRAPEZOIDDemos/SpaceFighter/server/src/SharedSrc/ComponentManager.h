#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#ifdef CLIENT
	#undef ENGINE_REGISTER_H	
	#pragma once
	#include "SpaceFighter_client.h"
#endif /* CLIENT */

#include "XLib.h"

class EngineRegister;
class Component;


class ComponentManager {
public:

	void virtual update(EngineRegister &engineRegister, float dt);

protected:
	XLib::Vector<XLib::SharedPtr<Component>> container;
};

#endif /* MANAGER_H_INCLUDED */