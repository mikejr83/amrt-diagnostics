#include "settings.h"
#include "utilities.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ServoInput.h>
#include <stdlib.h>
#include <ArduinoLog.h>

#include "display.h"
#include "uiTests.h"
#include "logo.h"

void rxPulseTimer();

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ServoInputPin<RX_PIN_IN> recieverInput;
ServoInputPin<AMRT_PIN_IN> amrtInput;

void setup()
{
  Serial.begin(115200);

#ifndef DISABLE_LOGGING
  Log.begin(LOG_LEVEL, &Serial);
#endif

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  showStartup(display);

  Log.infoln(F("Set-up complete"));
  Serial.flush();
}

unsigned long lastUpdate = 0;
unsigned long rxOutput = 0;
unsigned long amrtOutput = 0;

void loop()
{
  unsigned long currentRxOutput = recieverInput.getPulseRaw();
  unsigned long currentAmrtOutput = amrtInput.getPulseRaw();

  if (currentRxOutput > MIN_PWM_SIGNAL && currentRxOutput < 2250)
  {
    rxOutput = currentRxOutput;
  }

  if (currentAmrtOutput > MIN_PWM_SIGNAL && currentAmrtOutput < 2250)
  {
    amrtOutput = currentAmrtOutput;
  }

  unsigned long currentTime = millis();
  if (currentTime - lastUpdate >= REFRESH_RATE)
  {
    lastUpdate = currentTime;
    displayStatus(display, rxOutput, amrtOutput);
  }
}