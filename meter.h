// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef meter_H_
#define meter_H_
#include "Arduino.h"

//add your includes for the project meter here
class Meter {
	
public:
	Meter();
	void begin(uint8_t);
	void setCalibrationValues(uint8_t values[]);
	void value(uint8_t);
	
	
	
private:
	
};




//Do not add code below this line
#endif /* meter_H_ */
