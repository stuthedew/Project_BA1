#include <avr/pgmspace.h>
#include "meter.h"
#include <TinyWireS.h>

#define I2C_SLAVE_ADDR 0x16

#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif


prog_uchar hundredsMeterCalibrationVals[] PROGMEM = {
  6, 36, 60, 85, 110, 130, 154, 176, 200, 228};
prog_uchar tensMeterCalibrationVals[] PROGMEM = {
  44, 67, 91, 115, 139, 164, 186, 207, 230, 255};
prog_uchar onesMeterCalibrationVals[] PROGMEM = {
  10, 34, 62, 88, 114, 142, 166, 193, 220, 245};  




//meter pins
#define hundredsPin 7
#define tensPin 5
#define onesPin 8

Meter onesMeter;
Meter tensMeter;
Meter hundredsMeter;

int counter = 0;

void setup(){
  TinyWireS.begin(I2C_SLAVE_ADDR);
  onesMeter.begin(onesPin);
  tensMeter.begin(tensPin);
  hundredsMeter.begin(hundredsPin);




  setCalibration(&onesMeter, onesMeterCalibrationVals);

  setCalibration(&tensMeter, tensMeterCalibrationVals);

  setCalibration(&hundredsMeter, hundredsMeterCalibrationVals);




  displayValue(999, 2);
  delay(500);
  rampValue(0, 2);


}


void loop(){

  byte bytesRcvd[2];
  int i = 0;
  while(TinyWireS.available()){           // got I2C input!

    bytesRcvd[i] = TinyWireS.read();
    i++;
  }
  if(i > 0){           
    int payload = bytesRcvd[0] << 8;
    payload |= bytesRcvd[1];
    rampValue(payload, 3);
  }
  delay(10);
}


void setCalibration(Meter *m, prog_uchar *uc){
  uint8_t tmpAry[10];
  for(int i = 0; i < 10; i++){
    tmpAry[i] = pgm_read_byte_near(uc + i);  
  }
  m->setCalibrationValues(tmpAry);

}


void displayValue(int distance, unsigned int rampDelay) {
  int hundreds = distance / 100;

  int tens = (distance - (hundreds * 100)) / 10;
  int ones = distance % 10;
  hundredsMeter.displayValue(hundreds, rampDelay);
  delay(10);
  onesMeter.displayValue(ones, rampDelay);
  delay(10);
  tensMeter.displayValue(tens, rampDelay);
}



void rampValue(int distance, uint8_t rampVal){
  int hundreds = distance / 100;

  int tens = (distance - (hundreds * 100)) / 10;
  int ones = distance % 10;
  int delta[3];
  uint8_t maxDelta = 0;
  delta[0] = lookupByte(hundreds, hundredsMeterCalibrationVals) - hundredsMeter.currentPosition;
  delta[1] = lookupByte(tens, tensMeterCalibrationVals) - tensMeter.currentPosition;
  delta[2] = lookupByte(ones, onesMeterCalibrationVals) - onesMeter.currentPosition;

  for(int i = 0; i < 3; i++){
    if(abs(delta[i]) > maxDelta){
      maxDelta = abs(delta[i]);
    }
  }
  uint8_t hVal;
  for(int i = 0; i <= maxDelta; i++){
    hVal = hundredsMeter.currentPosition + map(i, 0, maxDelta, 0, delta[0]);
    hundredsMeter.displayRaw(hVal);
    delay(rampVal);
    onesMeter.displayRaw(onesMeter.currentPosition + map(i, 0, maxDelta, 0, delta[2]));
    delay(rampVal);
    tensMeter.displayRaw(tensMeter.currentPosition + map(i, 0, maxDelta, 0, delta[1]));
    delay(rampVal);
  }

hundredsMeter.currentPosition =lookupByte(hundreds, hundredsMeterCalibrationVals);
tensMeter.currentPosition =lookupByte(tens, tensMeterCalibrationVals);
onesMeter.currentPosition =lookupByte(ones, onesMeterCalibrationVals);

}

uint8_t lookupByte(uint8_t numVal, prog_uchar *uc){
  return pgm_read_byte_near(uc + numVal);  

}







