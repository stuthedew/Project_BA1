// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef button_H_
#define button_H_
#include "Arduino.h"

//add your includes for the project button here
class Button{
public: 
	Button();
	void begin(uint8_t);
	void blink(unsigned long);
	
	
private:
	uint8_t _ledPin;
	
	
};




//Do not add code below this line
#endif /* button_H_ */
