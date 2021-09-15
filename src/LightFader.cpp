
#include "LightFader.h"

LightFader::LightFader(int pwmPin, int switchUpPin, int switchDownPin)
{
    m_pinLight = pwmPin;
    m_pinSwitchUp = switchUpPin;
    m_pinSwitchDown = switchDownPin;
}

void LightFader::setup()
{
    pinMode(m_pinLight, OUTPUT);
    pinMode(m_pinSwitchUp, INPUT);
    pinMode(m_pinSwitchDown, INPUT);

    analogWrite(m_pinSwitchUp, 0);
    analogWrite(m_pinSwitchDown, 0);
    analogWrite(m_pinLight, m_lightVal);  
}

void LightFader::update()
{
    int switchThreshold = 800;
    int m_threshold = 250;
    bool isFadingUp = (analogRead(m_pinSwitchUp) > switchThreshold) ? true : false;
    bool isFadingDown = (analogRead(m_pinSwitchDown) > switchThreshold) ? true : false;
    int startLightVal = 10;

    // First we need to tell the difference between long press and quick press
    if (isFadingUp || isFadingDown){
        if (!m_isButtonPressed){
            m_isButtonPressed = true;
            m_buttonPressStartTime = millis();
        }
    }
    else {
        m_isButtonPressed = false;
    }
    
    unsigned long elapsedTime = millis() - m_buttonPressStartTime;


    if (m_isButtonPressed && elapsedTime > m_threshold){
        // if the button has been pressed for more than 250ms, then this is a long press
        m_isLongPress = true;    
    }
    else if (!m_isShortPress && !m_isButtonPressed && elapsedTime < m_threshold){
        Serial.println("Short press");
        m_isShortPress = true;
        m_isLongPress = false;   
    }    



    // Now control light and consume the events    
    if (m_isLongPress){

        m_isLongPress = false;
        m_isLightOn = true;

        if (isFadingUp){
            m_lightVal += 1;
        }
        else {
            m_lightVal -= 1;
        }

        if (m_lightVal > 255){
            m_lightVal = 255;
        }
        else if (m_lightVal < startLightVal){
            m_lightVal = startLightVal;
        }

        Serial.print("Long press"); 
        Serial.print(" UP: "); 
        Serial.print(isFadingUp); 
        Serial.print(" DWN: "); 
        Serial.print(isFadingDown);
        Serial.print(" Val: "); 
        Serial.print(m_lightVal);
        Serial.println();

        analogWrite(m_pinLight, m_lightVal/10);        

    }
    
    if (m_isShortPress && elapsedTime > 300){
        m_isShortPress = false;        
        if (!m_isLightOn){
            // Turn on
            if (m_lightVal < startLightVal){
                m_lightVal = startLightVal;
            }
            m_isLightOn = true;
            analogWrite(m_pinLight, m_lightVal/10);
        }
        else {
            // Turn off (but remember last light val)
            m_isLightOn = false;
            analogWrite(m_pinLight, 0);
        }
    }


}