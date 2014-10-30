#ifndef TIMER_MANAGER_H_INCLUDED
#define TIMER_MANAGER_H_INCLUDED

#include <vector>
#include <memory>
#include "handle.h"
#include "timercomponent.h"

typedef std::shared_ptr<TimerComponent> TimerComponentPtr;

class HandleManager;

class TimerManager {
public:
	void update(HandleManager &handleManager, double dt);
	Handle createComponent(HandleManager &handleManager, double timerLength = -1);

private:
	std::vector<TimerComponentPtr> container;
};

#endif