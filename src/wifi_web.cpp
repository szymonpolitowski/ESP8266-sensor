#include "wifi_web.hpp"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "mem_flash.hpp"

const char* ssid = "ESP8266_AP";
const char* password = "12345678";

IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

static bool web_status = true;
ESP8266WebServer server(80);

static void initWifiAccessPoint(void);
static void handleRoot();
static void handleSubmit();
static void handleShutdown();
static String maskPassword(String password);

void initWifiWebServer(void)
{
    initWifiAccessPoint();

    server.on("/", handleRoot);
    server.on("/submit", HTTP_POST, handleSubmit);
    server.on("/shutdown", handleShutdown);
    server.begin();
    Serial.println("HTTP server started");
}

bool loopWifiWebServer(void)
{
    server.handleClient();
    return web_status;
}

static void initWifiAccessPoint(void)
{
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_IP, gateway, subnet);
    if (WiFi.softAPConfig(local_IP, gateway, subnet)) {
        Serial.println("AP Config Success");
    } else {
        Serial.println("AP Config Failed");
    }
    Serial.println("Access Point Created");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
}

static void handleRoot()
{
    String nameStr = String(getDeviceName().c_str());
    String intervalStr = String(std::to_string(getDeviceInterval()).c_str());
    String ssidStr = String(getWiFiSSID().c_str());
    String passStr = String(getWiFiPassword().c_str());
    String mqttServerStr = String(getMqttServer().c_str());
    String mqttPortStr = String(getMqttPort().c_str());

    String html = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<title>ESP8266 Sensor AP</title></head><body>";
    html += "<h1>ESP8266 Sensor config</h1>";
    html += "<form action=\"/submit\" method=\"POST\">";
    html += "<label for=\"field_dev_name\">Device name: </label>";
    html += "<input type=\"text\" id=\"field_dev_name\" name=\"field_dev_name\" value=\"" + nameStr + "\"><br><br>";
    html += "<label for=\"field_dev_interval\">Interval seconds: </label>";
    html += "<input type=\"text\" id=\"field_dev_interval\" name=\"field_dev_interval\" value=\"" + intervalStr + "\"><br><br>";
    html += "<label for=\"field_wifi_ssid\">WiFi SSID: </label>";
    html += "<input type=\"text\" id=\"field_wifi_ssid\" name=\"field_wifi_ssid\" value=\"" + ssidStr + "\"><br><br>";
    html += "<label for=\"field_wifi_pass\">WiFi Password: </label>";
    html += "<input type=\"password\" id=\"field_wifi_pass\" name=\"field_wifi_pass\" value=\"" + passStr + "\"><br><br>";
    html += "<label for=\"field_mqtt_server\">MQTT Server: </label>";
    html += "<input type=\"text\" id=\"field_mqtt_server\" name=\"field_mqtt_server\" value=\"" + mqttServerStr + "\"><br><br>";
    html += "<label for=\"field_mqtt_port\">MQTT Port: </label>";
    html += "<input type=\"text\" id=\"field_mqtt_port\" name=\"field_mqtt_port\" value=\"" + mqttPortStr + "\"><br><br>";
    html += "<input type=\"submit\" value=\"Submit\">";
    html += "</form><br>";
    html += "<button onclick=\"location.href='/shutdown'\">Shutdown Web Server</button>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}

static void handleSubmit()
{
    String temp_device_name;
    String temp_device_interval;
    String temp_wifi_ssid;
    String temp_wifi_pass;
    String temp_mqtt_server;
    String temp_mqtt_port;

    if (server.method() == HTTP_POST) {
        temp_device_name = server.arg("field_dev_name");
        temp_device_interval = server.arg("field_dev_interval");
        temp_wifi_ssid = server.arg("field_wifi_ssid");
        temp_wifi_pass = server.arg("field_wifi_pass");
        temp_mqtt_server = server.arg("field_mqtt_server");
        temp_mqtt_port = server.arg("field_mqtt_port");

        Serial.println("WebServer Device name: " + temp_device_name);
        Serial.println("WebServer Device interval: " + temp_device_interval);
        Serial.println("WebServer WiFi SSID: " + temp_wifi_ssid);
        Serial.println("WebServer WiFi Password: " + temp_wifi_pass);
        Serial.println("WebServer MQTT Server: " + temp_mqtt_server);
        Serial.println("WebServer MQTT Port: " + temp_mqtt_port);

        String response = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'>";
        response += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
        response += "<title>ESP8266 AP</title></head><body>";
        response += "<h1>Data has been stored in internal memory</h1>";
        response += "<p>Device name: " + temp_device_name + "</p>";
        response += "<p>Interval seconds: " + temp_device_interval + "</p>";
        response += "<p>WiFi SSID: " + temp_wifi_ssid + "</p>";
        response += "<p>WiFi Password: " + maskPassword(temp_wifi_pass) + "</p>";
        response += "<p>MQTT Server: " + temp_mqtt_server + "</p>";
        response += "<p>MQTT Port: " + temp_mqtt_port + "</p>";
        response += "<button onclick=\"location.href='/'\">Go to Main Page</button>";
        response += "<button onclick=\"location.href='/shutdown'\">Shutdown Web Server</button>";
        response += "</body></html>";

        server.send(200, "text/html", response);

        setDeviceName(std::string(temp_device_name.c_str()));
        setDeviceInterval(std::stoul(std::string(temp_device_interval.c_str())));
        setWiFiSSID(std::string(temp_wifi_ssid.c_str()));
        setWiFiPassword(std::string(temp_wifi_pass.c_str()));
        setMqttServer(std::string(temp_mqtt_server.c_str()));
        setMqttPort(std::string(temp_mqtt_port.c_str()));
    } else {
        server.send(405, "text/html", "<h1>405 Method Not Allowed</h1>");
    }
}

static void handleShutdown() {
    server.send(200, "text/html", "<h1>Server is shutting down...</h1>");
    delay(1000); 
    server.stop();
    WiFi.softAPdisconnect(true);
    Serial.println("Server stopped and AP disconnected");
    web_status = false;
}

static String maskPassword(String password)
{
    unsigned int len = password.length();
    String masked_password;
    masked_password.clear();
    for(unsigned int i = 0; i < len; i++)
    {
        masked_password += '*';
    }
    return masked_password;
}