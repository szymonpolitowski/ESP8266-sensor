#include "mem_flash.hpp"
#include <LittleFS.h>
#include <string>

std::string device_name;
std::string device_interval;

void initMemFlash(void)
{
    if (!LittleFS.begin()) {
        Serial.println("Błąd inicjalizacji systemu plików SPIFFS");
        return;
    }
    Serial.println("Memory Flash initialized");

    File file;

    file = LittleFS.open("/device_name.txt", "r");
    if (file) 
    {
        while (file.available()) 
        {
            Serial.write(file.read());
        }
        file.close();
    }
    else 
    {
        Serial.println("Błąd otwarcia pliku do odczytu");
    }
    



    file = LittleFS.open("/device_name.txt", "w");
    if (!file) {
        Serial.println("Błąd otwarcia pliku do zapisu");
        return;
    }
    file.println("ESP-test");
    file.close();

}
