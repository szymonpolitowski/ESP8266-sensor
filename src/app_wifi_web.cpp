#include "app_wifi_web.hpp"
#include "wifi_web.hpp"
#include "button.hpp"
#include <Arduino.h>

const unsigned long time_to_wait = 10000;

void appWifiWebServer(void)
{
    Serial.println("Hold button for 2 seconds and than release it to enable Web Server Task...");
    buttonInit();
    bool enableWebServer = false;
    unsigned long int waiting_time_start = millis();
    while(time_to_wait > millis() - waiting_time_start)
    {
        if(isButtonLongPressed())
        {
            enableWebServer = true;
            break;
        }
        delay(10);
    }
    buttonDeinit();

    if(enableWebServer)
    {
        initWifiWebServer();
        while(loopWifiWebServer());
    } 
    else 
    {
        Serial.println("Web Server was not triggered.");
    }
}