// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef lock_H_
#define lock_H_
#include "Arduino.h"
#include <Servo.h>

#define openPosition 45
#define closedPosition 75

//add your includes for the project lock here
class Lock{
	
public:
	Lock(uint8_t servoPin, uint8_t pwrPin);
	void begin();
	void open();
	void close();
	
	
private:
	uint8_t _openPos, _closePos;
	uint8_t _servoPin, _pwrPin;
	Servo _latchServo;
	void _moveServo(uint8_t);
};






//Do not add code below this line
#endif /* lock_H_ */
