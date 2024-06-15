#include "wifi_sta.hpp"
#include <ESP8266WiFi.h>
#include "mem_flash.hpp"

void wifiConnect()
{
    Serial.print("Wifi: Connecting to ");
    Serial.print(getWiFiSSID().c_str());
    Serial.print(" ");

    WiFi.begin(getWiFiSSID().c_str(), getWiFiPassword().c_str());

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    Serial.print("Connected to ");
    Serial.print(getWiFiSSID().c_str());
    Serial.println("");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("RSSI: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
}