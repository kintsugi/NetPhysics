#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#ifdef CLIENT
	#undef ENGINE_REGISTER_H	
	#pragma once
	#include "SpaceFighter_client.h"
#endif /* CLIENT */

#include "XLib.h"
#include "Handle.h"

class Component;
class HandleManager;

class ComponentManager {
public:

	void update(HandleManager &handleManager);
	Handle createComponent(Component* component);

protected:

	XLib::Vector<XLib::SharedPtr<Component>> container;
};

#endif /* MANAGER_H_INCLUDED */