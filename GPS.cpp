#include <Arduino.h>
#include "GPS.h"



volatile char c;

/*************************************************************************/
/******************************* GPS Class **************************/
/*************************************************************************/

/*--------------------------------PUBLIC---------------------------------*/

GPS::GPS() :
		mySerial(3,2), AF_GPS(&mySerial) {

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

/*--------------------------------PRIVATE---------------------------------*/








/*---------------------------Static Functions-------------------------------*/

SIGNAL(TIMER0_COMPA_vect) {
	c = AF_GPS.read();
}

/*------------------------End of Static Functions----------------------------*/

