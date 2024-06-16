#include "sensor_bme.hpp"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void sensorBmeInit()
{
    bme.begin(0x76);
}

float sensorBmeGetTemperature()
{
    float temp = bme.readTemperature();
    if(NAN != temp)
        return temp;

    return -100.0f;
}

float sensorBmeGetHumidity()
{
    float hum = bme.readHumidity();
    if(NAN != hum)
        return hum;

    return -100.0f;
}

float sensorBmeGetPressure()
{
    float pressure = bme.readPressure();
    if(NAN != pressure)
        return pressure/100.0f;

    return -100.0f;
}