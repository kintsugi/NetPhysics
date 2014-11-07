#pragma once

#include "SpaceFighter_client.h"

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