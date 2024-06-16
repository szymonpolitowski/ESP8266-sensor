#pragma once
#include <string>

void initMemFlash(void);

void setDeviceName(std::string name);
void setDeviceInterval(unsigned int interval);
void setWiFiSSID(std::string ssid);
void setWiFiPassword(std::string pass);
void setMqttServer(std::string mqtt_s);
void setMqttPort(std::string mqtt_p);
void setMqttMainTopic(std::string mqtt_mt);

std::string getDeviceName();
unsigned int getDeviceInterval();
std::string getWiFiSSID();
std::string getWiFiPassword();
std::string getMqttServer();
std::string getMqttPort();
std::string getMqttMainTopic();

// void testMemFlash();