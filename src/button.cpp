#include "button.hpp"
#include <Arduino.h>

// GPIO 0 -> D3 NodeMCU
const int buttonPin = 0;
const int buttonLongPressedTime = 1500; // ms

volatile bool buttonPressed = false;
volatile bool buttonLongPressed = false;
volatile unsigned long buttonPressStartTime = 0;

IRAM_ATTR void handleButtonInterrupt();

void buttonInit(void)
{
    pinMode(buttonPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonInterrupt, CHANGE);
}

bool isButtonLongPressed(void)
{
    if(buttonLongPressed)
    {
        buttonLongPressed = false;
        return true;
    }
    
    return false;
}


IRAM_ATTR void handleButtonInterrupt() {
    if (digitalRead(buttonPin) == LOW) { 
        buttonPressStartTime = millis();
    } else { 
        unsigned long pressDuration = millis() - buttonPressStartTime; 
        if (pressDuration >= buttonLongPressedTime) {
            buttonLongPressed = true;
        } else {
            buttonPressed = true;
        }
    }
}
