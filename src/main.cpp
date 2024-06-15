#include <Arduino.h>
#include "app_wifi_web.hpp"
#include "mem_flash.hpp"

void setup() {
  delay(100);
  Serial.begin(115200);
  while(!Serial);

  Serial.println("Hello, ESP8266!");

  initMemFlash();

  // appWifiWebServer();

}

void loop() {

  Serial.println("Running...");
  delay(1000);
}
