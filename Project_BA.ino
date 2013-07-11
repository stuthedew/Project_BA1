#include "cache.h"
#include <Flash.h>
#include <EEPROM.h>
#include "button.h"
#include "counter.h"
#include "data.h"
#include "latch.h"
#include <Servo.h>
#include "meter.h"
#include "GPS.h"
#include <Adafruit_GPS.h>

#define killPin 3
#define buttonPin 6

#define countPin 4

Cache cache(killPin);

unsigned long timer;



void setup(){
  
  
  pinMode(buttonPin, OUTPUT);
  digitalWrite(buttonPin, LOW);
  cache.begin();
  



}




void loop(){
  timer = millis();
  while(millis() - timer < 5000){
    blinkButton();
  }

  
}

void blinkButton(){
  digitalWrite(buttonPin, HIGH);
  delay(500);
  digitalWrite(buttonPin, LOW);
  delay(500);
  
  
}






