#include <Arduino.h>
#include "wifi_web.hpp"
#include "button.hpp"

void setup() {
  delay(100);
  Serial.begin(115200);
  while(!Serial);

  Serial.println("Hello, ESP8266!");
  buttonInit();

  initWifiWebServer();
  while(loopWifiWebServer());
}

void loop() {

  Serial.println("Running...");
  delay(1000);
}
