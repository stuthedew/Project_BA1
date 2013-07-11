#include "meter.h"

Meter::Meter() {

}

void Meter::begin(uint8_t meterPin) {
	_meterPin = meterPin;
	pinMode(_meterPin, OUTPUT);
	digitalWrite(_meterPin, LOW);

}


void Meter::displayValue(uint8_t value){
	Serial.println(value);
	Serial.println(_calValues[value]);
	_rampPWM(_calValues[value]);
	
	
}

void Meter::_displayRawValue(uint8_t rawVal) {

}

void Meter::_rampPWM(uint8_t rawVal, unsigned int rampDelay) {
	static uint8_t oldVal;

	int deltaVal = rawVal - oldVal;
	

	if (deltaVal == 0) {
		return;
	}
	//direction handling
	if(deltaVal > 0) {
		for(int i = oldVal + 1; i <= rawVal; i += 1) {
			analogWrite(_meterPin, i);
			delay(rampDelay);
		}
	}

	else if(deltaVal < 0) {

		for(int i = oldVal - 1; i >= rawVal; i -= 1) {
			analogWrite(_meterPin, i);
			delay(rampDelay);
		}

	}
	oldVal = rawVal;
}

void Meter::setCalibrationValues(unsigned char calValues[]){
	for(int i = 0; i< 10; i++){
	
	_calValues[i] = calValues[i];
	}

}
