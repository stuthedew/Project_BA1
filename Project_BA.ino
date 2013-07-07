#include "cache.h"
#include <Flash.h>
//#include <modules/button.h>
//#include <modules/counter.h>
#include "data.h"
//#include <modules/lock.h>
//#include <modules/meter.h>
#include "GPS.h"

#include <Adafruit_GPS.h>
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

#define cs   10
#define dc   9
#define rst  8

#define RED 255
#define GREEN 0
#define BLUE 0

TFT TFTscreen = TFT(cs, dc, rst);
int oldDist;
int i = 0;
int xPos, yPos;
char sensorPrintout[4];

GPS GPS;


Data locData;

void setup(){
  GPS.begin();
  Serial.begin(115200);
  delay(100);
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);

  delay(1000);

  TFTscreen.stroke(255,255,255);
  TFTscreen.setTextSize(2);
  TFTscreen.text("Km Away:\n ",0,0);
  TFTscreen.setTextSize(5);
  xPos = TFTscreen.width()/2 - 30;
  yPos = TFTscreen.height()/2 - 20;



}


uint32_t timer = millis();


void loop(){

  GPS.checkAndParse();

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 3000) { 
    timer = millis(); // reset the timer


    if (GPS.fix) {


      locData.setCurrentLocation(GPS.latitude, GPS.lat, GPS.longitude,GPS.lon);

      int dist = round(locData.distanceInKilometers());

      Serial.println();
      Serial.print("Distance: ");
      Serial.print(dist);
      Serial.println(" km");
      Serial.print("HDOP: ");
      Serial.println(GPS.HDOP);
      Serial.print("Fix Quality: ");
      Serial.println(GPS.fixQuality);
      Serial.print("Satellites: ");
      Serial.println(GPS.satellites);


      if(oldDist != dist){
        

        TFTscreen.stroke(0,0,0);
        TFTscreen.text(sensorPrintout, xPos, yPos);
        String sensorVal = String(dist);
        sensorVal.toCharArray(sensorPrintout, 4);

        TFTscreen.stroke(BLUE,GREEN,RED);
        TFTscreen.text(sensorPrintout, xPos, yPos);
        oldDist = dist;
      }
    }

  }
}






