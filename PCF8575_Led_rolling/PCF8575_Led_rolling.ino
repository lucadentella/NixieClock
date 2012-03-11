#include <Wire.h>

#define PCF8575_ADDRESS  0x20
unsigned int outputs;
  
void setup() {

  Wire.begin();
  
  Serial.begin(57600);
  Serial.println("PCF8575 LED rolling demo");
  
  outputs = 0xFFFE;
}

void loop() {

  byte low = outputs & 0x00FF;
  byte high = outputs >> 8;
  Wire.beginTransmission(PCF8575_ADDRESS);
  Wire.write(low);
  Wire.write(high);
  Wire.endTransmission();
  
  if(outputs == 0x7FFF) outputs = 0xFFFE;
  else outputs = (outputs << 1) + 1;
  
  delay(200);
}
