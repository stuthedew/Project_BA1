#include "cache.h"

prog_uchar onesMeterCalibrationVals[] PROGMEM = {9, 37, 66, 94, 122, 151, 176, 203, 230, 255};
prog_uchar tensMeterCalibrationVals[] PROGMEM = {46, 70, 93, 117, 141, 164, 186, 207, 229, 255};
prog_uchar hundredsMeterCalibrationVals[] PROGMEM = {4, 31, 56, 79, 102, 124, 145, 168, 193, 217};

Cache::Cache(uint8_t killPin) :
		_counter(), _data(), _latch(), _GPS(), _hundredsMeter(), _tensMeter(), _onesMeter() {

	_killPin = killPin;

}

void Cache::begin() {

	pinMode(_killPin, OUTPUT);
	digitalWrite(_killPin, LOW);

}

void Cache::attachCounter(uint8_t counterPin) {
	_counter.begin(counterPin);

}

uint8_t Cache::getMode() {
	return EEPROM.read(modeAddress);

}

void Cache::setMode(mode_e cacheMode) {
	EEPROM.write(modeAddress, cacheMode);

}

void Cache::attachGPS(uint8_t enablePin) {
	_GPS.begin(enablePin);
	_GPS.sleep();

}

void Cache::attachLatch(uint8_t servoPin, uint8_t pwrPin) {
	_latch.begin(servoPin, pwrPin);

}

void Cache::attachMeters(uint8_t hundredsMeterPin, uint8_t tensMeterPin,
		uint8_t onesMeterPin) {
	unsigned char tmpAry[10];

	for (int i = 0; i < 10; i++) {
		tmpAry[i] = pgm_read_byte_near(onesMeterCalibrationVals + i);
	}
	_onesMeter.setCalibrationValues(tmpAry);

	for (int i = 0; i < 10; i++) {
		tmpAry[i] = pgm_read_byte_near(tensMeterCalibrationVals + i);
	}
	_tensMeter.setCalibrationValues(tmpAry);

	for (int i = 0; i < 10; i++) {
		tmpAry[i] = pgm_read_byte_near(hundredsMeterCalibrationVals + i);
	}
	_hundredsMeter.setCalibrationValues(tmpAry);

}

void Cache::firstRun() {
	_latch.open();
	unsigned int timer = millis();
	while (millis() - timer < 5000) {
		_button.blink(500);
	}

	timer = millis();
	while (millis() - timer < 5000) {
		_button.blink(250);
	}

	_latch.close();

	timer = millis();
	while (millis() - timer < 20000) {
		_button.blink(250);
	}
	timer = millis();
	_counter.reset();
	setMode (activeGameMode);

}

void Cache::display(int distance){
	uint8_t hundreds = distance / 100;
	_hundredsMeter.display(hundreds);
	
	uint8_t tens = (distance - (hundreds *100)) / 10;
	_tensMeter.display(tens);
	
	uint8_t ones = distance % 10;
	_onesMeter.display(ones);
}

void Cache::activeGame() {
	_GPS.wake();

	_timeout = millis();
	while (!_GPS.fix && millis() - _timeout < 120000) {
		_button.blink(500);
	}
	if (!_GPS.fix) {
		return;
	}


	for (int i = 0; i < 5; i++) {
		if (_GPS.checkAndParse()) {
			break;
		}
		delay(1000);
	}
	
	_data.setCurrentLocation(_GPS.latitude, _GPS.lat, _GPS.longitude, _GPS.lon);
	
	display(_data.distanceInKilometers());
	delay(20000);
	incrementTryCount();

}

void Cache::close() {
	_latch.close();

}

void Cache::incrementTryCount(){
	EEPROM.write(tryCount, EEPROM.read(tryCount) + 1);
}

void Cache::shutdown() {
	digitalWrite(_killPin, HIGH);

}

