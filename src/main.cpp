#include <Arduino.h>
#include "app_wifi_web.hpp"
#include "mem_flash.hpp"
#include "wifi_sta.hpp"
#include "app_mqtt.hpp"
#include "app_sensor.hpp"

void setup()
{
  delay(100);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("");
  Serial.println("Hello, ESP8266!");

  initMemFlash();

  appWifiWebServer();

  wifiConnect();
  mqttInit();
  sensorInit();
  sensorSetInterval(getDeviceInterval());
}

void loop()
{
  sensorLoop();
  mqttLoop();
  delay(10);
}
