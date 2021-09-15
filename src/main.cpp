
#include <Arduino.h>
#include "Pins.h"
#include "LightFader.h"


Pins pins;
LightFader fader1 = LightFader(5, A3, A5);
LightFader fader2 = LightFader(6, A1, A2);

int val = 1;

void setup()
{
    Serial.begin(115200);
    Serial.print("Starting...");
    fader1.setup();
    fader2.setup();
}

void loop()
{   
    fader1.update();
    fader2.update();

}