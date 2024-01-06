/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/
#include "settings.h"
#include "utilities.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdlib.h>
#include <ArduinoLog.h>

#include "uiTests.h"
#include "logo.h"

void rxPulseTimer();

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile long startTime = 0;
volatile long currentTime = 0;
volatile long rxPulses = 0;
int pulseWidth = 0;

void displayStatus(long rxValue, long amrtValue)
{
  char rxValBuffer[10];
  char amrtValBuffer[10];

  itoa(rxValue, rxValBuffer, 10);
  itoa(amrtValue, amrtValBuffer, 10);

  Log.noticeln("RX Value: %s", rxValBuffer);
  Log.noticeln("AMRT Value: %s", amrtValBuffer);

  display.clearDisplay();

  display.setTextSize(1);              // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);                 // Use full 256 char 'Code Page 437' font

  display.setCursor(0, 0); // Start at top-left corner
  display.write("From Receiver: ");
  display.write(rxValBuffer);

  display.setCursor(0, 8);
  display.write("From AMRT: ");
  display.write(amrtValBuffer);

  display.display();
}

void setup()
{
  Serial.begin(9600);

#ifndef DISABLE_LOGGING
  Log.begin(LOG_LEVEL, &Serial);
#endif

  pinMode(RX_PIN_IN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RX_PIN_IN), rxPulseTimer, CHANGE);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();

  Log.infoln(F("Set-up complete"));
  Serial.flush();
}

void loop()
{
  if (rxPulses > 750 && rxPulses <= 2200)
  {
    displayStatus(rxPulses, 1200);
  }
}

void rxPulseTimer()
{
  currentTime = micros();
  if (currentTime > startTime)
  {
    rxPulses = currentTime - startTime;
    startTime = currentTime;
  }
}