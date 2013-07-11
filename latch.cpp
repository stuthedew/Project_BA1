#include "latch.h"

/*************************************************************************/
/******************************* Latch Class **************************/
/*************************************************************************/

/*--------------------------------PUBLIC---------------------------------*/

Latch::Latch() :
		_latchServo() {
	_closePos = closedPosition;
	_openPos = openPosition;

}

void Latch::begin(uint8_t servoPin, uint8_t pwrPin) {
	_servoPin = servoPin;
	_pwrPin = pwrPin;
	pinMode(_servoPin, OUTPUT);
	pinMode(_pwrPin, OUTPUT);
	digitalWrite(_pwrPin, LOW);
	_latchServo.attach(_servoPin);
}

void Latch::close() {

	_moveServo(_closePos);

}

void Latch::open() {
	_moveServo (_openPos);
}

/*--------------------------------PRIVATE---------------------------------*/
void Latch::_moveServo(uint8_t latchPos) {
	digitalWrite(_pwrPin, HIGH);
	delay(10);
	_latchServo.write(latchPos);
	delay(250);
	digitalWrite(_pwrPin, LOW);

}
