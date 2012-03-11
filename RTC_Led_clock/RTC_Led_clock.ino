#include <Wire.h>
#include "RTClib.h"

#define PCF8575_ADDRESS  0x20

byte display_minute;
byte display_hour;

RTC_DS1307 RTC;

void setup() {

  Serial.begin(57600);
  Serial.println("RTC Led clock");
  Serial.println();

  Wire.begin();
  RTC.begin();
}

void loop() {

  DateTime now = RTC.now();  
  byte rtc_minute = bin2bcd(now.minute());
  byte rtc_hour = bin2bcd(now.hour());

  if(display_minute != rtc_minute || display_hour != rtc_hour) {
    
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.println(now.minute(), DEC);
    
    display_minute = rtc_minute;
    display_hour = rtc_hour;
    byte inverted_hour = revert(display_hour);
    sendOutputs(display_minute, inverted_hour);
  }
}

void sendOutputs(byte low, byte high) {
  
  Wire.beginTransmission(PCF8575_ADDRESS);
  Wire.write(~low);
  Wire.write(~high);
  Wire.endTransmission();
}

byte bin2bcd (uint8_t val) { return val + 6 * (val / 10); }

byte revert(byte in) {
  
  byte out = 0;
  for(int i = 0; i < 7; i++) {
    if(in & 1) out = out + 1;
    out = out << 1;
    in = in >> 1;
  }
  if(in & 1) out = out + 1;
  return out;
}
