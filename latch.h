// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef lock_H_
#define lock_H_
#include "Arduino.h"
#include <Servo.h>

#ifndef openPosition
#define openPosition 45
#endif

#ifndef closedPosition
#define closedPosition 75
#endif

//add your includes for the project latch here
class Latch{
	
public:
	Latch();
	void begin(uint8_t, uint8_t);
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
