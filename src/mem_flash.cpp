#include "mem_flash.hpp"
#include <LittleFS.h>

#define DEFAULT_STR_DEVICE_NAME         "ESP-Sensor"
#define DEFAULT_STR_DEVICE_INTERVAL     "300"
#define DEFAULT_STR_WIFI_SSID           "YourWifiSSID"
#define DEFAULT_STR_WIFI_PASS           "TopSecretPassword"
#define DEFAULT_STR_MQTT_SERVER         "192.168.0.2"
#define DEFAULT_STR_MQTT_PORT           "1883"
#define DEFAULT_STR_MQTT_MAIN_TOPIC     "sensor/"

#define FILE_NAME_DEVICE_NAME           "/device_name.txt"
#define FILE_NAME_DEVICE_INTERVAL       "/device_interval.txt"
#define FILE_NAME_WIFI_SSID             "/device_wifi_ssid.txt"
#define FILE_NAME_WIFI_PASS             "/device_wifi_pass.txt"
#define FILE_NAME_MQTT_SERVER           "/device_mqtt_server.txt"
#define FILE_NAME_MQTT_PORT             "/device_mqtt_port.txt"
#define FILE_NAME_MQTT_MAIN_TOPIC       "/device_mqtt_main_topic.txt"

static std::string device_name = DEFAULT_STR_DEVICE_NAME;
static std::string device_interval = DEFAULT_STR_DEVICE_INTERVAL;
static std::string wifi_ssid = DEFAULT_STR_WIFI_SSID;
static std::string wifi_pass = DEFAULT_STR_WIFI_PASS;
static std::string mqtt_server = DEFAULT_STR_MQTT_SERVER;
static std::string mqtt_port = DEFAULT_STR_MQTT_PORT;
static std::string mqtt_main_topic = DEFAULT_STR_MQTT_MAIN_TOPIC;

static bool mem_initialized = false;

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

    if(!readFromFile(FILE_NAME_WIFI_SSID, wifi_ssid))
    {
        wifi_ssid = DEFAULT_STR_WIFI_SSID;
        writeToFile(FILE_NAME_WIFI_SSID, wifi_ssid);
    }

    if(!readFromFile(FILE_NAME_WIFI_PASS, wifi_pass))
    {
        wifi_pass = DEFAULT_STR_WIFI_PASS;
        writeToFile(FILE_NAME_WIFI_PASS, wifi_pass);
    }

    if(!readFromFile(FILE_NAME_MQTT_SERVER, mqtt_server))
    {
        mqtt_server = DEFAULT_STR_MQTT_SERVER;
        writeToFile(FILE_NAME_MQTT_SERVER, mqtt_server);
    }

    if(!readFromFile(FILE_NAME_MQTT_PORT, mqtt_port))
    {
        mqtt_port = DEFAULT_STR_MQTT_PORT;
        writeToFile(FILE_NAME_MQTT_PORT, mqtt_port);
    }

    if(!readFromFile(FILE_NAME_MQTT_MAIN_TOPIC, mqtt_main_topic))
    {
        mqtt_main_topic = DEFAULT_STR_MQTT_MAIN_TOPIC;
        writeToFile(FILE_NAME_MQTT_MAIN_TOPIC, mqtt_main_topic);
    }
}

void setDeviceName(std::string name)
{
    device_name = name;
    writeToFile(FILE_NAME_DEVICE_NAME, device_name);
}

void setDeviceInterval(unsigned int interval)
{   
    device_interval = std::to_string(interval);
    writeToFile(FILE_NAME_DEVICE_INTERVAL, device_interval);
}

void setWiFiSSID(std::string ssid)
{
    wifi_ssid = ssid;
    writeToFile(FILE_NAME_WIFI_SSID, wifi_ssid);
}
void setWiFiPassword(std::string pass)
{
    wifi_pass = pass;
    writeToFile(FILE_NAME_WIFI_PASS, wifi_pass);
}

void setMqttServer(std::string mqtt_s)
{
    mqtt_server = mqtt_s;
    writeToFile(FILE_NAME_MQTT_SERVER, mqtt_server);
}

void setMqttPort(std::string mqtt_p)
{
    mqtt_port = mqtt_p;
    writeToFile(FILE_NAME_MQTT_PORT, mqtt_port);
}

void setMqttMainTopic(std::string mqtt_mt)
{
    mqtt_main_topic = mqtt_mt;
    writeToFile(FILE_NAME_MQTT_MAIN_TOPIC, mqtt_main_topic);
}

std::string getDeviceName()
{
    return device_name;
}

unsigned int getDeviceInterval()
{
    return std::stoul(device_interval);
}

std::string getWiFiSSID()
{
    return wifi_ssid;
}
std::string getWiFiPassword()
{
    return wifi_pass;
}

std::string getMqttServer()
{
    return mqtt_server;
}

std::string getMqttPort()
{
    return mqtt_port;
}

std::string getMqttMainTopic()
{
    return mqtt_main_topic;
}

// void testMemFlash()
// {
//     Serial.println("1. dev name");
//     Serial.println(getDeviceName().c_str());
//     Serial.println("1. dev interval");
//     Serial.println(getDeviceInterval());

//     std::string new_name = "myNewName";
//     setDeviceName(new_name);
//     setDeviceInterval(500);

//     Serial.println("2. dev name");
//     Serial.println(getDeviceName().c_str());
//     Serial.println("2. dev interval");
//     Serial.println(getDeviceInterval());
// }

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
