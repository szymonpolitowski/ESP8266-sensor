#include "mem_flash.hpp"
#include <LittleFS.h>

#define DEFAULT_STR_DEVICE_NAME         "ESP-Sensor"
#define DEFAULT_STR_DEVICE_INTERVAL     "300"

#define FILE_NAME_DEVICE_NAME           "/device_name.txt"
#define FILE_NAME_DEVICE_INTERVAL       "/device_interval.txt"

static std::string device_name;
static std::string device_interval;

static bool mem_initialized = false;

// static bool getDeviceNameFromMemory(std::string &name);
// static bool getDeviceIntervalFromMemory(std::string &interval);

static bool writeToFile(const char *filename, std::string str);
static bool readFromFile(const char *filename, std::string &str);

void initMemFlash(void)
{
    if (!LittleFS.begin()) {
        Serial.println("LittleFS - file system initialization error!");
        return;
    }
    mem_initialized = true;
    Serial.println("Memory Flash initialized");

    // set defaults if memory is empty
    if(!readFromFile(FILE_NAME_DEVICE_NAME, device_name))
    {
        device_name = DEFAULT_STR_DEVICE_NAME;
        writeToFile(FILE_NAME_DEVICE_NAME, device_name);
    }
        
    if(!readFromFile(FILE_NAME_DEVICE_INTERVAL, device_interval))
    {
        device_interval = DEFAULT_STR_DEVICE_INTERVAL;
        writeToFile(FILE_NAME_DEVICE_INTERVAL, device_interval);
    }
        

}

static bool writeToFile(const char *filename, std::string str)
{
    if(!mem_initialized) return false;

    File file = LittleFS.open(filename, "w");
    if (!file) {
        Serial.print("Error opening file ");
        Serial.print(filename);
        Serial.println(" for writing");
        return false;
    }
    file.println(str.c_str());
    file.close();
    
    return true;
}

static bool readFromFile(const char *filename, std::string &str)
{
    if(!mem_initialized) return false;

    File file = LittleFS.open(filename, "r");
    if (file) 
    {
        str.clear();
        while (file.available()) 
        {
            char c = file.read();
            str += c;
        }
        file.close();
        Serial.print("File ");
        Serial.print(filename);
        Serial.print(": ");
        Serial.println(str.c_str());
        
        return true;
    }
    else 
    {
        Serial.print("Error opening file ");
        Serial.print(filename);
        Serial.println(" for reading");
    }

    return false;
}



// bool setDeviceNameToMemory(std::string name)
// {
//     if(!mem_initialized) return false;

//     File file = LittleFS.open("/device_name.txt", "w");
//     if (!file) {
//         Serial.println("Error opening file device_name.txt for writing");
//         return false;
//     }
//     file.println(name.c_str());
//     file.close();
    
//     return true;
// }

// bool setDeviceIntervalToMemory(std::string interval)
// {
//     if(!mem_initialized) return false;

//     File file = LittleFS.open("/device_interval.txt", "w");
//     if (!file) {
//         Serial.println("Error opening file device_interval.txt for writing");
//         return false;
//     }
//     file.println(interval.c_str());
//     file.close();
    
//     return true;
// }

// bool getDeviceNameFromMemory(std::string &name)
// {
//     if(!mem_initialized) return false;

//     File file = LittleFS.open("/device_name.txt", "r");
//     if (file) 
//     {
//         name.clear();
//         while (file.available()) 
//         {
//             char c = file.read();
//             name += c;
//         }
//         file.close();
//         Serial.print("File device_name.txt: ");
//         Serial.println(name.c_str());
//     }
//     else 
//     {
//         Serial.println("Error opening file for reading");
//     }

//     return true;
// }

// bool getDeviceIntervalFromMemory(std::string &interval)
// {
//     if(!mem_initialized) return false;

//     File file = LittleFS.open("/device_interval.txt", "r");
//     if (file) 
//     {
//         interval.clear();
//         while (file.available()) 
//         {
//             char c = file.read();
//             interval += c;
//         }
//         file.close();
//         Serial.print("File device_interval.txt: ");
//         Serial.println(interval.c_str());
//     }
//     else 
//     {
//         Serial.println("Error opening file for reading");
//     }

//     return true;
// }