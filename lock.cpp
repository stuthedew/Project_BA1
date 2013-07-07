#include "lock.h"

/*************************************************************************/
/******************************* Lock Class **************************/
/*************************************************************************/

/*--------------------------------PUBLIC---------------------------------*/

Lock::Lock(uint8_t servoPin, uint8_t pwrPin) :
		_latchServo() {
	_servoPin = servoPin;
	_pwrPin = pwrPin;
	_closePos = closedPosition;
	_openPos = openPosition;

}

void Lock::begin() {
	pinMode(_servoPin, OUTPUT);
	pinMode(_pwrPin, OUTPUT);
	digitalWrite(_pwrPin, LOW);
	_latchServo.attach(_servoPin);
}

void Lock::close() {

	_moveServo(_closePos);

}

void Lock::open() {
	_moveServo (_openPos);
}

/*--------------------------------PRIVATE---------------------------------*/
void Lock::_moveServo(uint8_t latchPos) {
	digitalWrite(_pwrPin, HIGH);
	delay(10);
	_latchServo.write(latchPos);
	delay(250);
	digitalWrite(_pwrPin, LOW);

}
