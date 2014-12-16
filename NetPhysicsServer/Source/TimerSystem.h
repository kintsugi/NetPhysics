#ifndef TIMER_SYSTEM_H_INCLUDED
#define TIMER_SYSTEM_H_INCLUDED

#include "System.h"
#include "ComponentList.h"

namespace NetPhysics {
	class TimerSystem : public System {
	public:

		TimerSystem();
		void update(Register &reg, const double dt);

	private:

		ComponentList componentList;
	};
}

#endif /* TIMER_SYSTEM_H_INCLUDED */