#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#ifdef CLIENT
	#undef COMPONENT_H_INCLUDED	
	#pragma once
	#include UE4_PROJECT_H
#endif /* CLIENT */
#include "Handle.h"

//Base class for components
class Component {
public:
	Component(Handle newHandle);

	Handle getHandle();
	Handle getParent();
	void setParent(Handle parentHandle);

private:
	Handle handle;
	Handle parent;
};

#endif