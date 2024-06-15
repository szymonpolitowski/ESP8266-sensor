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
// static void handleButton();

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

static void handleRoot() {

    String html = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<title>ESP8266 AP</title></head><body>";
    html += "<h1>Welcome to ESP8266 Access Point</h1>";
    html += "<form action=\"/submit\" method=\"POST\">";
    html += "<label for=\"field_dev_name\">Device name: </label>";
    html += "<input type=\"text\" id=\"field_dev_name\" name=\"field_dev_name\"><br><br>";
    html += "<label for=\"field_dev_interval\">Interval seconds: </label>";
    html += "<input type=\"text\" id=\"field_dev_interval\" name=\"field_dev_interval\"><br><br>";
    html += "<input type=\"submit\" value=\"Submit\">";
    html += "</form><br>";
    html += "<button onclick=\"location.href='/shutdown'\">Shutdown Server</button>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}

static void handleSubmit() {

    String temp_device_name;
    String temp_device_interval;

    if (server.method() == HTTP_POST) {
        temp_device_name = server.arg("field_dev_name");
        temp_device_interval = server.arg("field_dev_interval");
        Serial.println("WebServer Device name: " + temp_device_name);
        Serial.println("WebServer Device interval: " + temp_device_interval);

        String response = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'>";
        response += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
        response += "<title>ESP8266 AP</title></head><body>";
        response += "<h1>Data Received</h1>";
        response += "<p>Device name: " + temp_device_name + "</p>";
        response += "<p>Interval seconds: " + temp_device_interval + "</p>";
        response += "<button onclick=\"location.href='/'\">Go to Main Page</button>";
        response += "<button onclick=\"location.href='/shutdown'\">Shutdown Server</button>";
        response += "</body></html>";

        server.send(200, "text/html", response);
    } else {
        server.send(405, "text/html", "<h1>405 Method Not Allowed</h1>");
    }

    setDeviceName(std::string(temp_device_name.c_str()));
    setDeviceInterval(std::stoul(std::string(temp_device_interval.c_str())));

}

static void handleShutdown() {
    server.send(200, "text/html", "<h1>Server is shutting down...</h1>");
    delay(1000); // Krótkie opóźnienie na wyświetlenie wiadomości
    server.stop();
    WiFi.softAPdisconnect(true);
    Serial.println("Server stopped and AP disconnected");
    web_status = false;
}