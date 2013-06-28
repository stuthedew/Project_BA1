#include "cache.h"
#include <Flash.h>
//#include <modules/button.h>
//#include <modules/counter.h>
#include "data.h"
//#include <modules/lock.h>
//#include <modules/meter.h>
#include "GPS.h"

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
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

SoftwareSerial mySerial(3, 2);

Adafruit_GPS GPS(&mySerial);

#define GPSECHO  false

boolean usingInterrupt = true;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

Data locData;

void setup(){
  Serial.begin(115200);
  GPS.begin(9600);
  delay(100);
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);

  useInterrupt(true);
  delay(1000);

  mySerial.println(PMTK_Q_RELEASE);
  TFTscreen.stroke(255,255,255);
  TFTscreen.setTextSize(2);
  TFTscreen.text("Km Away:\n ",0,0);
  TFTscreen.setTextSize(5);
  xPos = TFTscreen.width()/2 - 30;
  yPos = TFTscreen.height()/2 - 20;
  Serial.println();



}



void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } 
  else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();


void loop(){


  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 3000) { 
    timer = millis(); // reset the timer


    if (GPS.fix) {


      locData.setCurrentLocation(GPS.latitude, GPS.lat, GPS.longitude,GPS.lon);

      int dist = round(locData.distanceInKilometers());

      Serial.println(" miles from opening!");
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





