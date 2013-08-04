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
#include "GPS.h"
#include <Adafruit_GPS.h>
#include <Wire.h>


#define tryCountAddress 25
#define boxStatusAddress 24

#define displayAddress 0x16



	


//add your includes for the project cache here
class Cache {
	
public:
	Cache(uint8_t);
	void begin();
	void attachButton(uint8_t);
	void attachCounter(uint8_t, uint8_t);
	void attachGPS(uint8_t);
	void attachLatch(uint8_t, uint8_t);
	void attachMeters(uint8_t, uint8_t, uint8_t);
	
	char readGPS();
	
	void firstRun();
	
	void activeGame();
	
	void close();
	void open();
	uint8_t attemptCounter();
	
	uint8_t getMode();
	void setMode(uint8_t);
	void incrementTryCount();
	uint8_t status();
	void shutdown();
	
private:
	void _display(int);
	Latch _latch;
	Data _data;
	GPS _GPS;
	Counter _counter;
	Button _button;
	
	uint8_t _oldTicks;
	
	unsigned long _timeout;
	uint8_t _killPin;
	
	
	
	
};







//Do not add code below this line
#endif /* cache_H_ */
