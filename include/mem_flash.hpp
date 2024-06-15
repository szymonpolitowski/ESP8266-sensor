#pragma once
#include <string>

void initMemFlash(void);

void setDeviceName(std::string name);
void setDeviceInterval(unsigned int interval);
void setWiFiSSID(std::string ssid);
void setWiFiPassword(std::string pass);

std::string getDeviceName();
unsigned int getDeviceInterval();
std::string getWiFiSSID();
std::string getWiFiPassword();

// void testMemFlash();