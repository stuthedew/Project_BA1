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
#include <SoftwareSerial.h>

class GPS {
public:
	GPS();
	void begin();
	uint8_t checkAndPars();
	Adafruit_GPS AF_GPS;


private:
	SoftwareSerial mySerial;


};





//Do not add code below this line
#endif /* GPS_H_ */
