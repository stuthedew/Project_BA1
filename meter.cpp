
#include "meter.h"


Meter::Meter(){
	
	
}


void Meter::begin(uint8_t meterPin){
	_meterPin = meterPin;
	pinMode(_meterPin, OUTPUT);
	digitalWrite(_meterPin, LOW);
	
	
}