// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef meter_H_
#define meter_H_
#include "Arduino.h"
#include <avr/pgmspace.h>

//add your includes for the project meter here
class Meter {
	
public:
	Meter();
	void begin(uint8_t);
	
	void displayValue(uint8_t, unsigned int rampDelay = 2);
	
	void setCalibrationValues(unsigned char calVal[]);
	
	void displayRaw(uint8_t);

        uint8_t currentPosition;

	
	
	
private:
	uint8_t _meterPin;
	uint8_t _calValues[10];
	void _rampPWM(uint8_t, unsigned int);
};  




//Do not add code below this line
#endif /* meter_H_ */
