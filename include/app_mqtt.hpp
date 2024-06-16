#pragma once
#include <Arduino.h>

void mqttInit(void);
void mqttLoop(void);
bool mqttServerConnected(void);

void mqttPublishTemperature(float temperature);
void mqttPublishHumidity(float humidity);
void mqttPublishPressure(float pressure);
