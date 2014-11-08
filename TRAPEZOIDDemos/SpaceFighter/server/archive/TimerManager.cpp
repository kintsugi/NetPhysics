#include "timermanager.h"
#include "handlemanager.h"

void TimerManager::update(HandleManager &handleManager, double dt) {
	for (auto iter = container.begin(); iter != container.end();) {
		(*iter)->update(dt);
		if (!handleManager.get((*iter)->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}

Handle TimerManager::createComponent(HandleManager &handleManager, double timerLength) {
	if (timerLength == -1)
		container.push_back(TimerComponentPtr(new TimerComponent(handleManager)));
	else
		container.push_back(TimerComponentPtr(new TimerComponent(handleManager, timerLength)));
	return container.back()->getHandle();
}