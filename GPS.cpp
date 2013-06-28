#include <Arduino.h>
#include "GPS.h"

char c;
volatile boolean readFlag = 0;

/*************************************************************************/
/******************************* GPS Class **************************/
/*************************************************************************/

/*--------------------------------PUBLIC---------------------------------*/

GPS::GPS() :
		mySerial(3, 2), AF_GPS(&mySerial) {

}

void GPS::begin() {

	AF_GPS.begin(9600);
	AF_GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	AF_GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);

	//set up Interrupts to read GPS serial data
	OCR0A = 0xAF;
	TIMSK0 |= _BV(OCIE0A);

	delay(1000);

}

uint8_t GPS::checkAndParse() {
	//code: 1 == success, 2 == no new NMEA data, 3 == failed to parse
	if (readFlag) {
		c = AF_GPS.read();
		readFlag = 0;

		if (AF_GPS.newNMEAreceived()) {

			if (!AF_GPS.parse(AF_GPS.lastNMEA())) { // this also sets the newNMEAreceived() flag to false
				return 3; // we can fail to parse a sentence in which case we should just wait for another
			}
			_update();
			return 1;
		}
	} else {
		return 2;
	}

}

/*--------------------------------PRIVATE---------------------------------*/

void GPS::_update() {

	hour = AF_GPS.hour;
	minute = AF_GPS.minute;
	seconds = AF_GPS.seconds;
	year = AF_GPS.year;
	month = AF_GPS.month;
	day = AF_GPS.day;
	milliseconds = AF_GPS.milliseconds;
	latitude = AF_GPS.latitude;
	longitude = AF_GPS.longitude;
	geoidHeight = AF_GPS.geoidheight;
	altitude = AF_GPS.altitude;
	speed = AF_GPS.speed;
	angle = AF_GPS.angle;
	magVariation = AF_GPS.magvariation;
	HDOP = AF_GPS.HDOP;
	lat = AF_GPS.lat;
	lon = AF_GPS.lon;
	mag = AF_GPS.mag;
	fix = AF_GPS.fix;
	fixQuality = AF_GPS.fixquality;
	satellites = AF_GPS.satellites;

}

/***************************** End of GPS Class *************************/
/*************************************************************************/

/*---------------------------Static Functions-------------------------------*/

SIGNAL(TIMER0_COMPA_vect) {
	readFlag = 1;
}

/*------------------------End of Static Functions----------------------------*/

