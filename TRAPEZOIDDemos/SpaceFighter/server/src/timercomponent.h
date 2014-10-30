#ifndef TIMER_COMPONENT_H_INCLUDED
#define TIMER_COMPONENT_H_INCLUDED

#include "handle.h"

class HandleManager;

enum TimerMode {
	COUNT_DOWN,
	STOP_WATCH,
};

class TimerComponent {
public:

	//starts timer in stop watch mode
	TimerComponent(HandleManager &handleManager);
	//Starts timer in countdown mode
	TimerComponent(HandleManager &handleManager, double timerLength);

	void update(double dt);
	void setMode(TimerMode timerMode);

	//All modes
	void stop();
	void play();
	void pause();
	bool isPlaying();
	double getTimeElapsed();

	//Count down mode only
	double getLength();
	double getTimeLeft();
	void setLength(double timerLength);
	void addLength(double add);
	
	Handle getHandle();

private:
	Handle handle;
	TimerMode mode;
	double length;
	double elapsed;
	bool isPaused;
	
};

#endif