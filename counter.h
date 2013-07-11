// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef counter_H_
#define counter_H_
#include "Arduino.h"

#ifndef old_ticks
#define old_ticks 0
#endif

//add your includes for the project counter here
class Counter{
	
public:
	Counter();
	void begin(uint8_t);
	void resetCounter(uint8_t);
	void tick();
	
	
	
private:
	uint8_t _counterPin;
	
};




//Do not add code below this line
#endif /* counter_H_ */
