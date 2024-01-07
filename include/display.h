#pragma once

#include <Adafruit_SSD1306.h>

void showStartup(Adafruit_SSD1306 display);

void scrollText(Adafruit_SSD1306 display, bool leftAndRight, char *str);

void displayStatus(Adafruit_SSD1306 display, long rxValue, long amrtValue);