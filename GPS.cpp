#include <Arduino.h>
#include "GPS.h"

volatile char c;

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

uint8_t GPS::checkAndParse(){
	//code: 1 == success, 2 == no new NMEA data, 3 == failed to parse
	if (AF_GPS.newNMEAreceived()) {
	    // a tricky thing here is if we print the NMEA sentence, or data
	    // we end up not listening and catching other sentences!
	    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
	    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

	    if (!AF_GPS.parse(AF_GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
	      return 3;  // we can fail to parse a sentence in which case we should just wait for another

	    return 1;
	  }
	else{
		return 2;
	}


}

/*--------------------------------PRIVATE---------------------------------*/





/***************************** End of GPS Class *************************/
/*************************************************************************/




/*---------------------------Static Functions-------------------------------*/

SIGNAL(TIMER0_COMPA_vect) {
	c = AF_GPS.read();
}

/*------------------------End of Static Functions----------------------------*/

