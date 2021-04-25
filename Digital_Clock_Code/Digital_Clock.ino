#include "SevSeg.h"
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
SevSeg Display;
const int ledPin =  A0;
unsigned long timeDisplay;
unsigned long currentMillis;
unsigned int Hour;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 500;
void setup()
{
  pinMode(ledPin, OUTPUT);
  byte numDigits = 6;
  byte digitPins[] = {10, 11, 12, 13, A1, A2};
  byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
  bool resistorsOnSegments = false; // false = resistors are on digit pins
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_ANODE;
  Display.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  Display.setBrightness(100);
}
void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    if (ledState == LOW)
    {
      ledState = HIGH;
    }
    else
    {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }
  tmElements_t tm;
  if (RTC.read(tm))
  {
    Hour = tm.Hour;
    if (tm.Hour > 12)
{
if (tm.Hour == 13) Hour = 1;
if (tm.Hour == 14) Hour = 2;
if (tm.Hour == 15) Hour = 3;
if (tm.Hour == 16) Hour = 4;
if (tm.Hour == 17) Hour = 5;
if (tm.Hour == 18) Hour = 6;
if (tm.Hour == 19) Hour = 7;
if (tm.Hour == 20) Hour = 8;
if (tm.Hour == 21) Hour = 9;
if (tm.Hour == 22) Hour = 10;
if (tm.Hour == 23) Hour = 11;
}
else
{
if (tm.Hour == 0) Hour = 12;
}
 
    timeDisplay = (Hour * 100 + tm.Minute) * 100L + tm.Second;
  }
  else {
    timeDisplay = 888888; // error
  }
  Display.setNumber(timeDisplay);
  Display.refreshDisplay();
}
