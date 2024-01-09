#include "settings.h"
#include "display.h"

#include <ArduinoLog.h>

void scrollText(Adafruit_SSD1306 display, bool leftAndRight, const char *str)
{
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextWrap(false);
    display.setTextColor(SSD1306_WHITE);
    int16_t x;
    long minX;
    x = display.width();
    minX = 12 * strlen(str);

    for (int i = x; i < minX; i++)
    {
        int val = x - i;
        display.clearDisplay();
        display.setCursor(val, 10);
        display.print(str);
        display.display();
    }
    if (leftAndRight)
    {
        delay(500);
        for (int i = (minX - 1); i > x - 1; i--)
        {
            display.clearDisplay();
            display.setCursor(-(i - x), 10);
            display.print(str);
            display.display();
        }
    }
}

void showStartup(Adafruit_SSD1306 display)
{
    display.clearDisplay();

    scrollText(display, true, "Carl's Recycled Airplane Parts");
    delay(1000);
    scrollText(display, false, "AMRT Diagnosis Tool");

    delay(1000);
}

const char *empty = "\0";

void displayStatus(Adafruit_SSD1306 display, long rxValue, long amrtValue)
{
    char rxValBuffer[10];
    char amrtValBuffer[10];

    itoa(rxValue, rxValBuffer, 10);
    itoa(amrtValue, amrtValBuffer, 10);

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

    const char *lineOne, *lineTwo;

    if (rxValue < MIN_PWM_SIGNAL)
    {
        Log.traceln("Showing no rx input");
        lineOne = "No RX Input!";
    }
    else
    {
        lineOne = empty;
    }

    if (amrtValue < MIN_PWM_SIGNAL)
    {
        if (strlen(lineOne) > 0)
        {
            lineTwo = "No AMRT Input!";
        }
        else
        {
            lineOne = "No AMRT Input!";
        }
    }
    else
    {
        lineTwo = empty;
    }

    if (strlen(lineOne) > 0)
    {
        display.setCursor(0, 16);
        display.write(lineOne);
    }

    if (strlen(lineTwo) > 0)
    {
        display.setCursor(0, 24);
        display.write(lineTwo);
    }

    display.display();
}