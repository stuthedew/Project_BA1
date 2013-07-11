#include "cache.h"
#include <Flash.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include "button.h"
#include "counter.h"
#include "data.h"
#include "latch.h"
#include <Servo.h>
#include "meter.h"
#include "GPS.h"
#include <Adafruit_GPS.h>

//Latch pins
#define servoPin 9
#define pwrPin 2

//meter pins
#define hundredsPin 3
#define tensPin 5
#define onesPin 6

//counter pin
#define counterPin 2

//GPS pin
#define GPS_enable_pin 7

//power kill pin
#define killPin 4

Cache cache(killPin);




void setup(){

  cache.begin();

  cache.attachLatch(servoPin, pwrPin);
  cache.attachMeters(hundredsPin, tensPin, onesPin);  
  cache.attachCounter(counterPin);
  cache.attachGPS(GPS_enable_pin);



}




void loop(){

  switch(cache.getMode()){
  case first_run:

    cache.setMode(activeGame);
    cache.shutdown();

    break;


  case activeGame:

    cache.shutdown();

    break;


  case found:

    cache.shutdown();

    break;

  case fail:

    cache.shutdown();

    break;

  }
}









