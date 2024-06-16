# ESP8266 Sensor

- [Moduł WIFI ESP8266](https://botland.com.pl/moduly-wifi-esp8266/8241-modul-wifi-esp8266-nodemcu-v3-5904422300630.html)
- [BME280](https://botland.com.pl/czujniki-cisnienia/11803-bme280-czujnik-wilgotnosci-temperatury-oraz-cisnienia-110kpa-i2cspi-33v-5904422366179.html)

## Wires

| BME280 | | ESP8266 |
|--|--|--|
| VCC | -> | 3V |
| GND | -> | G |
| SCL | -> | D1 |
| SDA | -> | D2 |

## Web Server Cfg

- press the Reset Button
- wait for about 1 second
- hold the Flash Button for about 2 seconds
- release the Flash Button
- connect to the ESP8266 Access Point (e.g. via a mobile phone)
- open a web browser and navigate to 192.168.1.4

| ESP8266 Access Point | |
|--|--|
| SSID | ESP8266_AP |
| Password | 12345678 |

| Name | e.g. value | comment |
|--|--|--|
| Device name | bedroom | Name of the device |
| Interval seconds | 300 | Measurement publishing interval |
| WiFi SSID | MyWifiSSID | Your Wifi SSID  |
| WiFi Password | TopSecretPassword | Your Wifi Password |
| MQTT Server | 192.168.1.15 | IP adress of the MQTT Broker |
| MQTT Port | 1883 | Port of the MQTT Broker |
| MQTT Main Topic | sensor/ | Main topic for published messages |

## MQTT Measurement Manager

| Topic | Payload example |
|--|--|
| **MQTT Main Topic**/**Device name**/temperature | 21.3 |
| **MQTT Main Topic**/**Device name**/humidity | 33.2 |
| **MQTT Main Topic**/**Device name**/pressure | 1003.0 |

- *MQTT Main Topic* is specified in the **Web Server Config**
- *Device name* is specified in the **Web Server Config**
