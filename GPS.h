// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef GPS_H_
#define GPS_H_
#include <Arduino.h>

//add your includes for the project GPS here
#include <Adafruit_GPS.h>

class GPS {
public:
	GPS();
	void begin();
	uint8_t checkAndParse();
	Adafruit_GPS AF_GPS;

	uint8_t hour, minute, seconds, year, month, day;
	uint16_t milliseconds;
	float latitude, longitude, geoidHeight, altitude;
	float speed, angle, magVariation, HDOP;
	char lat, lon, mag;
	boolean fix;
	uint8_t fixQuality, satellites;

	void sleep();
	
private:
	void _update();
	uint8_t _enablePin();

};

//Do not add code below this line
#endif /* GPS_H_ */
