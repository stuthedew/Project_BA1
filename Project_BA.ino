#include "cache.h"
#include <Flash.h>
//#include <modules/button.h>
//#include <modules/counter.h>
#include "data.h"
#include "lock.h"
#include <Servo.h>
//#include <modules/meter.h>
#include "GPS.h"

#include <Adafruit_GPS.h>

Lock latch(9, 2);



void setup(){
  latch.begin();



}




void loop(){
  latch.open();
  delay(5000);
  latch.close();
  delay(5000);

  
}






