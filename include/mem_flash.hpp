#pragma once
#include <string>

void initMemFlash(void);

bool setDeviceName(std::string name);
bool setDeviceInterval(std::string interval);

bool getDeviceName(std::string &name);
bool getDeviceInterval(std::string &interval);
