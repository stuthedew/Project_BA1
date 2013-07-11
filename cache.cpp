
#include "cache.h"




Cache::Cache(uint8_t killPin):_counter(), _latch(), _GPS(){
	_killPin = killPin;
	
	
}

void Cache::begin(){
	
	
	_GPS.begin();
	
	pinMode(_killPin, OUTPUT);
	digitalWrite(_killPin, LOW);
	

}

void Cache::attachCounter(uint8_t counterPin){
	_counter.begin(counterPin);
	
}

void Cache::attachLatch(uint8_t servoPin, uint8_t pwrPin){
	_latch.begin(servoPin, pwrPin);
	
}

void Cache::attachMeters(uint8_t hundredsMeterPin, uint8_t tensMeterPin, uint8_t onesMeterPin){
	
}

void Cache::shutdown(){
	digitalWrite(killPin, HIGH);
	
}