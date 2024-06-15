#include "mem_flash.hpp"
#include <LittleFS.h>

#define DEFAULT_DEVICE_NAME "ESP-Sensor"
#define DEFAULT_DEVICE_INTERVAL "300"

std::string device_name;
std::string device_interval;

static bool mem_initialized = false;

bool setDeviceNameToMemory(std::string name);
bool setDeviceIntervalToMemory(std::string interval);
bool getDeviceNameFromMemory(std::string &name);
bool getDeviceIntervalFromMemory(std::string &interval);

void initMemFlash(void)
{
    if (!LittleFS.begin()) {
        Serial.println("Błąd inicjalizacji systemu plików SPIFFS");
        return;
    }
    mem_initialized = true;
    Serial.println("Memory Flash initialized");
    std::string dev_name;
    getDeviceNameFromMemory(dev_name);
    dev_name.clear();
    dev_name = "newDeviceName";
    setDeviceNameToMemory(dev_name);
    getDeviceNameFromMemory(dev_name);

}

bool setDeviceNameToMemory(std::string name)
{
    if(!mem_initialized) return false;

    File file = LittleFS.open("/device_name.txt", "w");
    if (!file) {
        Serial.println("Error opening file device_name.txt for writing");
        return false;
    }
    file.println(name.c_str());
    file.close();
    
    return true;
}

bool setDeviceIntervalToMemory(std::string interval)
{
    if(!mem_initialized) return false;

    File file = LittleFS.open("/device_interval.txt", "w");
    if (!file) {
        Serial.println("Error opening file device_interval.txt for writing");
        return false;
    }
    file.println(interval.c_str());
    file.close();
    
    return true;
}

bool getDeviceNameFromMemory(std::string &name)
{
    if(!mem_initialized) return false;

    File file = LittleFS.open("/device_name.txt", "r");
    if (file) 
    {
        name.clear();
        while (file.available()) 
        {
            char c = file.read();
            name += c;
        }
        file.close();
        Serial.print("File device_name.txt: ");
        Serial.println(name.c_str());
    }
    else 
    {
        Serial.println("Error opening file for reading");
    }

    return true;
}

bool getDeviceIntervalFromMemory(std::string &interval)
{
    if(!mem_initialized) return false;

    File file = LittleFS.open("/device_interval.txt", "r");
    if (file) 
    {
        interval.clear();
        while (file.available()) 
        {
            char c = file.read();
            interval += c;
        }
        file.close();
        Serial.print("File device_interval.txt: ");
        Serial.println(interval.c_str());
    }
    else 
    {
        Serial.println("Error opening file for reading");
    }

    return true;
}