#include "cache.h"


/**********************************SECRET LOCATION*********************************/
//Latitude of Secret Location

/*		+	-
 *-
 * lat :	N	S
 * lon :	E	W
 */

	#define secLat 43.68071
	//Longitude of Secret Location
	#define secLon -114.362995

/**********************************SECRET LOCATION*********************************/


Cache::Cache(uint8_t killPin) :
		_counter(), _data(secLat, secLon), _latch(), _GPS() {

	_killPin = killPin;

}

void Cache::begin() {

	pinMode(_killPin, OUTPUT);
	digitalWrite(_killPin, LOW);
	Wire.begin();
	

}

void Cache::attachCounter(uint8_t counterPin, uint8_t oldTicks) {
	_counter.begin(counterPin);
	_oldTicks = oldTicks;
}

uint8_t Cache::attemptCounter(){
	
	return EEPROM.read(tryCountAddress);
}

uint8_t Cache::status(){
	return EEPROM.read(boxStatusAddress);
	
}
void Cache::attachButton(uint8_t buttonPin) {
	_button.begin(buttonPin);
}

void Cache::attachGPS(uint8_t enablePin) {
	_GPS.begin(enablePin);

}

void Cache::attachLatch(uint8_t servoPin, uint8_t pwrPin) {
	_latch.begin(servoPin, pwrPin);

}

void Cache::firstRun() {
	
	_latch.open();
	_GPS.sleep();
	unsigned int timerVal = millis();
	while (millis() - timerVal < 10000) {
		_button.blink(500);
	}

	timerVal = millis();
	while (millis() - timerVal < 10000) {
		_button.blink(250);
	}

	_latch.close();

	timerVal = millis();
	while (millis() - timerVal < 20000) {
		_button.blink(250);
	}
	_counter.reset(_oldTicks);
	EEPROM.write(boxStatusAddress, 0);
	EEPROM.write(tryCountAddress, 0);
	shutdown();

}

char Cache::readGPS(){
	return _GPS.read();
	
}

void Cache::activeGame() {
	_GPS.wake();
	for (int i = 0; i < 3; i++) {
		_button.blink(250);
	}
	_timeout = millis();
	while (!_GPS.fix && millis() - _timeout < 180000) {
		_GPS.checkAndParse();
		_button.blink(1000);
	}
	if (!_GPS.fix) {
		return;
	}

	for (int i = 0; i < 5; i++) {
		if (_GPS.checkAndParse() && _GPS.fixQuality < 1.5) {
			break;
		}
		delay(1100);
	}
	_GPS.sleep();
	_button.on();
	_data.setCurrentLocation(_GPS.latitude, _GPS.lat, _GPS.longitude, _GPS.lon);
	int distKm = min(_data.distanceInKilometers(), 999);
	if(distKm < 2){
		open();
		EEPROM.write(boxStatusAddress, 1);
		return;
	}
	else{
	_display(distKm);
	delay(20000);
	incrementTryCount();
	
	}
}

void Cache::close() {
	_latch.close();

}

void Cache::open() {
	
	unsigned int timerVal = millis();
		while (millis() - timerVal < 3000) {
			_button.blink(100);
		}
		
		_latch.open();
	
}

void Cache::incrementTryCount() {
	EEPROM.write(tryCountAddress, attemptCounter() + 1);
	_counter.tick();
	delay(10);
}

void Cache::shutdown() {
	digitalWrite(_killPin, HIGH);

}

void Cache::_display(int distanceVal) {
	uint8_t msb = distanceVal >> 8;
	uint8_t lsb = distanceVal & ~(0xFF << 8);

	Wire.beginTransmission(displayAddress);
	Wire.write(msb);
	Wire.write(lsb);
	Wire.endTransmission();

}

