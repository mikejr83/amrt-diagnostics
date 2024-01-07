#pragma once

#include <Adafruit_SSD1306.h>

void testdrawline(Adafruit_SSD1306 display);

void testdrawrect(Adafruit_SSD1306 display);      // Draw rectangles (outlines)

void testfillrect(Adafruit_SSD1306 display);      // Draw rectangles (filled)

void testdrawcircle(Adafruit_SSD1306 display);    // Draw circles (outlines)

void testfillcircle(Adafruit_SSD1306 display);    // Draw circles (filled)

void testdrawroundrect(Adafruit_SSD1306 display); // Draw rounded rectangles (outlines)

void testfillroundrect(Adafruit_SSD1306 display); // Draw rounded rectangles (filled)

void testdrawtriangle(Adafruit_SSD1306 display);  // Draw triangles (outlines)

void testfilltriangle(Adafruit_SSD1306 display);  // Draw triangles (filled)

void testdrawchar(Adafruit_SSD1306 display);      // Draw characters of the default font

void testdrawstyles(Adafruit_SSD1306 display);    // Draw 'stylized' characters

void testscrolltext(Adafruit_SSD1306 display);    // Draw scrolling text

void testdrawbitmap(Adafruit_SSD1306 display, const uint8_t *bitmap);    // Draw a small bitmap image

void testanimate(Adafruit_SSD1306 display, const uint8_t *bitmap, uint8_t w, uint8_t h);