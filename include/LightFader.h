#ifndef LightFader_H
#define LightFader_H

#include <Arduino.h>

class LightFader
{
private:
    int m_pinLight = 2;
    int m_pinSwitchUp = A0;
    int m_pinSwitchDown = A0;
    bool m_isButtonPressed = false;
    int m_lightVal = 0;
    unsigned long m_buttonPressStartTime = millis() + 99999;
    unsigned long m_slowLoopStartTime = millis() + 99999;
    bool m_isFadingUp = true;
    bool m_isLongPress = false;
    bool m_isShortPress = false;
    bool m_isLightOn = false;
public:
	// You can start out by creating a BME280 object with either software SPI (where all four pins can be any I/O) using
	//LightFader(int csPin, int sdaPin, int addrPin, int sclPin);
	// Or you can use hardware SPI. With hardware SPI you must use the hardware SPI pins for your Arduino
	//LightFader(int csPin);
	LightFader(int pwmPin, int switchUpPin, int switchDownPin);
	void setup();
	void update();



};

#endif