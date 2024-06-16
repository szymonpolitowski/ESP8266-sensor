#include "app_sensor.hpp"
#include "Arduino.h"
#include "sensor_bme.hpp"
#include "app_mqtt.hpp"

// default value stored in milliseconds
unsigned int sensor_interval = 5*60*1000;

static void sensorMeasureAndPublish();

void sensorInit()
{
    sensorBmeInit();
}

void sensorSetInterval(unsigned int interval_s)
{
    if(0 == interval_s)
        interval_s = 600; 

    sensor_interval = interval_s*1000;
    Serial.print("Measurement interval: ");
    Serial.print(sensor_interval);
    Serial.println("s")
}

void sensorLoop()
{   
    static unsigned int timestamp = millis();
    static bool first_publish = true;

    if(mqttServerConnected())
    {
        if(sensor_interval < millis() - timestamp || first_publish)
        {
            timestamp = millis();
            first_publish = false;

            sensorMeasureAndPublish();
        }
    }
}

static void sensorMeasureAndPublish()
{
    mqttPublishTemperature(sensorBmeGetTemperature());
    mqttPublishHumidity(sensorBmeGetHumidity());
    mqttPublishPressure(sensorBmeGetPressure());
}