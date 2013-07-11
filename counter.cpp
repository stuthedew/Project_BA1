#include "counter.h"

/*************************************************************************/
/******************************* Counter Class **************************/
/*************************************************************************/

/*--------------------------------PUBLIC---------------------------------*/

Counter::Counter() {
	

}

void Counter::begin(uint8_t counterPin) {
	_counterPin = counterPin;
	pinMode(_counterPin, OUTPUT);
	digitalWrite(_counterPin, LOW);

}

void Counter::reset() {

	if (old_ticks == 0) {
		return;
	}
	uint8_t clicks = 100 - old_ticks;

	for (int i = 0; i < clicks; i++) {
		tick();
	}

}

void Counter::tick() {
	digitalWrite(_counterPin, HIGH);
	delay(100);
	digitalWrite(_counterPin, LOW);
	delay(100);

}
