#pragma once
#include <memory>
#include "IEventAction.h"

class TimedEvent {
public:
	double beat = 0.0;
	bool triggered = false;

	std::unique_ptr<IEventAction> action;

	void update(double currentBeat);
};