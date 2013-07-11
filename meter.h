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
	
	void displayValue(uint8_t);
	
	void setCalibrationValues(unsigned char calVal[]);
	
	
	
	
	
private:
	uint8_t _meterPin;
	uint8_t _calValues[10];
	void _displayRawValue(uint8_t);
	void _rampPWM(uint8_t, unsigned int rampDelay=2);
	
};




//Do not add code below this line
#endif /* meter_H_ */
