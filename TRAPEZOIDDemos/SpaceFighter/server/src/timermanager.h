#ifndef TIMER_MANAGER_H_INCLUDED
#define TIMER_MANAGER_H_INCLUDED

#include "xlib.h"
#include "handle.h"
#include "timercomponent.h"

typedef std::shared_ptr<TimerComponent> TimerComponentPtr;

class HandleManager;

class TimerManager {
public:
	void update(HandleManager &handleManager, double dt);
	Handle createComponent(HandleManager &handleManager, double timerLength = -1);

private:
	XLib::Vector<TimerComponentPtr> container;
};

#endif