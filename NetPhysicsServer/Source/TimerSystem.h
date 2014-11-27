#ifndef TIMER_SYSTEM_H_INCLUDED
#define TIMER_SYSTEM_H_INCLUDED

#include "System.h"
#include "GameObjectFilter.h"

namespace NetPhysics {
	class TimerSystem : public System {
	public:

		TimerSystem();
		void update(Register &engineRegister, const double dt);

	private:

		GameObjectFilter filter;
	};
}

#endif /* TIMER_SYSTEM_H_INCLUDED */