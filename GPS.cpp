#include <Arduino.h>
#include "GPS.h"



volatile char c;

/*---------------------------Static Functions-------------------------------*/


static inline void handle_interrupts(volatile uint8_t *TCNTn, volatile uint8_t *OCRnA){


}

SIGNAL(TIMER0_COMPA_vect) {
	handle_interrupts(&TCNT0, &OCR0A);
}


/*------------------------End of Static Functions----------------------------*/


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










