#include "TimerComponent.h"
#include "HandleManager.h"
#include "ComponentType.h"

TimerComponent::TimerComponent(HandleManager &handleManager) :
	Component(TIMER, handleManager.add(this, COMPONENT)),
	mode(STOP_WATCH),
	length(0),
	elapsed(0),
	isPaused(true) {}

TimerComponent::TimerComponent(HandleManager &handleManager, double timerLength) : 
	Component(TIMER, handleManager.add(this, COMPONENT)),
	mode(COUNT_DOWN),
	elapsed(0),
	isPaused(true)
{
	length = length < 0 ? 0 : timerLength;
}

void TimerComponent::update(double dt) {
	if(!isPaused)
		elapsed += dt;
}

void TimerComponent::setMode(TimerMode timerMode) {
	mode = timerMode;
	stop();
}

void TimerComponent::stop() {
	isPaused = true;
	elapsed = 0;
}

void TimerComponent::play() {
	isPaused = false;
}

void TimerComponent::pause() {
	isPaused = true;
}

bool TimerComponent::isPlaying() {
	return !isPaused;
}

double TimerComponent::getTimeElapsed() {
	return elapsed;
}

double TimerComponent::getLength() {
	if (mode == COUNT_DOWN)
		return length;
	else
		return -1;
}

double TimerComponent::getTimeLeft() {
	if (mode == COUNT_DOWN) {
		return length - elapsed <= 0 ? 0 : length - elapsed;
	} else
		return -1;
}

void TimerComponent::setLength(double timerLength) {
	length = timerLength < 0 ? 0 : timerLength;
}

void TimerComponent::addLength(double add) {
	length += add < 0 ? 0 : add;
}