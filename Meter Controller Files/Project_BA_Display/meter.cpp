#include "meter.h"

Meter::Meter() {
  currentPosition = 0;

}

void Meter::begin(uint8_t meterPin) {
	_meterPin = meterPin;
	pinMode(_meterPin, OUTPUT);
	digitalWrite(_meterPin, LOW);

}


void Meter::displayValue(uint8_t value, unsigned int rampDelay){
	_rampPWM(_calValues[value], rampDelay);
	
	
}

void Meter::displayRaw(uint8_t rawVal){
 analogWrite(_meterPin, rawVal); 
}

void Meter::_rampPWM(uint8_t rawVal, unsigned int _rampDelay) {

	int deltaVal = rawVal - currentPosition;
	

	if (deltaVal == 0) {
		return;
	}
	//direction handling
	if(deltaVal > 0) {
		for(int i = currentPosition + 1; i <= rawVal; i += 1) {
			analogWrite(_meterPin, i);
			delay(_rampDelay);
		}
	}

	else if(deltaVal < 0) {

		for(int i = currentPosition - 1; i >= rawVal; i -= 1) {
			analogWrite(_meterPin, i);
			delay(_rampDelay);
		}

	}
	currentPosition = rawVal;
}

void Meter::setCalibrationValues(unsigned char calValues[]){
	for(int i = 0; i< 10; i++){
	
	_calValues[i] = calValues[i];
	}

}
