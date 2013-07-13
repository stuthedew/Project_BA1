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

#define modeAddress 0
#define tryCountAddress 1

typedef enum mode_e{first_run = 0, activeGameMode, found, fail} mode;



//add your includes for the project cache here
class Cache {
	
public:
	Cache(uint8_t);
	void begin();
	void attachButton(uint8_t);
	void attachCounter(uint8_t);
	void attachGPS(uint8_t);
	void attachLatch(uint8_t, uint8_t);
	void attachMeters(uint8_t, uint8_t, uint8_t);
	
	void firstRun();
	
	void activeGame();
	
	void close();
	
	void display(int);
	
	uint8_t getMode();
	void setMode(mode_e);
	void incrementTryCount();
	
	void shutdown();
	
private:
	Latch _latch;
	Data _data;
	GPS _GPS;
	Counter _counter;
	Button _button;
	
	Meter _hundredsMeter;
	Meter _tensMeter;
	Meter _onesMeter;
	
	unsigned long _timeout;
	uint8_t _killPin;
	
	
	
	
};







//Do not add code below this line
#endif /* cache_H_ */
