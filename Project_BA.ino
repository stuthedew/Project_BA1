#include "cache.h"
#include <Flash.h>
//#include <modules/button.h>
#include "counter.h"
#include "data.h"
#include "lock.h"
#include <Servo.h>
//#include <modules/meter.h>
#include "GPS.h"
#include <Adafruit_GPS.h>

#define killPin 3
#define buttonPin 6

Lock latch(9, 2);
Counter counter(8);

unsigned long timer;



void setup(){
  
  latch.begin();
  counter.begin();
  pinMode(killPin, OUTPUT);
  digitalWrite(killPin, LOW);
  pinMode(buttonPin, OUTPUT);
  digitalWrite(buttonPin, LOW);
  



}




void loop(){
  timer = millis();
  while(millis() - timer < 5000){
    blinkButton();
  }
  
  latch.close();
  delay(5000);
  latch.open();
  delay(1000);
  counter.tick();
  digitalWrite(killPin, HIGH);

  
}

void blinkButton(){
  digitalWrite(buttonPin, HIGH);
  delay(500);
  digitalWrite(buttonPin, LOW);
  delay(500);
  
  
}






