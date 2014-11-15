#ifndef COMPONENT_MANAGER_H_INCLUDED
#define COMPONENT_MANAGER_H_INCLUDED

#ifdef CLIENT
	#undef COMPONENT_MANAGER_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* CLIENT */
#include "XLib.h"
#include "ComponentHandle.h"

class Component;
class HandleManager;

class ComponentManager {
public:

	ComponentManager(ComponentType type);
	void update(HandleManager &handleManager);
	ComponentType getManagerType();
	ComponentHandle createComponent(Component* component);

private:
	ComponentType managerType;
	XLib::Vector<XLib::SharedPtr<Component>> container;

};

#endif /* MANAGER_H_INCLUDED */