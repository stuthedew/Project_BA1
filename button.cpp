
#include "button.h"

Button::Button(){
	
	
}

void Button::begin(uint8_t ledPin){
	
	_ledPin = ledPin;
	pinMode(_ledPin, OUTPUT);
	digitalWrite(_ledPin, LOW);
}

void Button::on(){
	digitalWrite(_ledPin, HIGH);
	
}

void Button::off(){
	digitalWrite(_ledPin, LOW);
	
}

void Button::blink(unsigned long blinkDelay){
	digitalWrite(_ledPin, HIGH);
	delay(blinkDelay);
	digitalWrite(_ledPin, LOW);
	delay(blinkDelay);
	
	
}
