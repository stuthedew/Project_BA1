// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef cache_H_
#define cache_H_
#include "Arduino.h"
#include <EEPROM.h>
#include <Flash.h>
#include "button.h"
#include "counter.h"
#include "data.h"
#include "latch.h"
#include <Servo.h>
#include "meter.h"
#include "GPS.h"
#include <Adafruit_GPS.h>

typedef enum mode_e{ first_run = 0, seek, found, fail} mode;

//add your includes for the project cache here
class Cache {
	
public:
	Cache(uint8_t);
	void begin();
	void attachCounter(uint8_t);
	void attachLatch(uint8_t, uint8_t);
	void attachMeters(uint8_t, uint8_t, uint8_t);
	
	void shutdown();
	
private:
	Latch _latch;
	GPS _GPS;
	Counter _counter;
	Data _data;
	uint8_t _killPin;
	
	
	
	
};







//Do not add code below this line
#endif /* cache_H_ */
