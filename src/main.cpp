#include <Arduino.h>
#include "app_wifi_web.hpp"

void setup() {
  delay(100);
  Serial.begin(115200);
  while(!Serial);

  Serial.println("Hello, ESP8266!");
  
  appWifiWebServer();

}

void loop() {

  Serial.println("Running...");
  delay(1000);
}
