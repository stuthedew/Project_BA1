#include "counter.h"

/*************************************************************************/
/******************************* Counter Class **************************/
/*************************************************************************/

/*--------------------------------PUBLIC---------------------------------*/

Counter::Counter(uint8_t counterPin) {
	_counterPin = counterPin;

}

void Counter::begin() {
	pinMode(_counterPin, OUTPUT);
	digitalWrite(_counterPin, LOW);

}

void Counter::resetCounter(uint8_t oldVal) {

	if (oldVal == 0) {
		return;
	}
	uint8_t clicks = 100 - oldVal;

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
