#pragma once
#include <string>

void initMemFlash(void);

void setDeviceName(std::string name);
void setDeviceInterval(unsigned int interval);

std::string getDeviceName();
unsigned int getDeviceInterval();

// void testMemFlash();