#include "cache.h"
#include <Flash.h>
#include "button.h"
#include "counter.h"
#include "data.h"
#include "latch.h"
#include <Servo.h>
#include "GPS.h"
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>


#define MAX_ATTEMPTS 50

#define killPin 17

#define buttonPin 6

#define counterPin 16

//Latch pins
#define servoPin 9
#define pwrPin 7

//GPS pin
#define enablePin 8

Cache Cache(killPin);


SIGNAL(TIMER0_COMPA_vect) {
  char c = Cache.readGPS();
}

void setup(){
Cache.begin();
Cache.attachCounter(counterPin, 26);
Cache.attachLatch(servoPin, pwrPin);
Cache.attachButton(buttonPin);
Cache.attachGPS(enablePin);

OCR0A = 0xAF;
TIMSK0 |= _BV(OCIE0A);

}


void loop(){
  
  if(Cache.attemptCounter() == 0xFF){
  Cache.firstRun();
    
  }
  else if(Cache.status() == true){
    Cache.open();
    Cache.shutdown();
  }
  else if( Cache.attemptCounter() <= MAX_ATTEMPTS){
    Cache.activeGame();
    Cache.shutdown();
    
  }

while(true);

}



