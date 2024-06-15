#include "mem_flash.hpp"
#include <LittleFS.h>

#define DEFAULT_STR_DEVICE_NAME         "ESP-Sensor"
#define DEFAULT_STR_DEVICE_INTERVAL     "300"

#define FILE_NAME_DEVICE_NAME           "/device_name.txt"
#define FILE_NAME_DEVICE_INTERVAL       "/device_interval.txt"

static std::string device_name;
static std::string device_interval;

static bool mem_initialized = false;

static bool writeToFile(const char *filename, std::string str);
static bool readFromFile(const char *filename, std::string &str);

// void printHexFromString(std::string str)
// {
//     for (char c : str) {
//         Serial.print("0x");
//         if ((unsigned char)c < 0x10) { // Dodaj wiodące zero, jeśli potrzeba
//             Serial.print("0");
//         }
//         Serial.print((unsigned char)c, HEX);
//         Serial.print(" ");
//     }
//     Serial.println();
// }

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
            if(c != '\r' && c != '\n')
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
