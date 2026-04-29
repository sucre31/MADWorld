#include "TimedEvent.h"


void TimedEvent::update(double currentBeat) {
	if (!triggered && currentBeat >= beat) {
		if (action) action->execute();
		triggered = true;
	}
}