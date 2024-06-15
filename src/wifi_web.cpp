#include "wifi_web.hpp"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

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
    String html = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>ESP8266 AP</title></head><body><h1>Welcome to ESP8266 Access Point</h1><form action=\"/submit\" method=\"POST\"><label for=\"field1\">Field 1:</label><input type=\"text\" id=\"field1\" name=\"field1\"><br><br><label for=\"field2\">Field 2:</label><input type=\"text\" id=\"field2\" name=\"field2\"><br><br><input type=\"submit\" value=\"Submit\"></form><br><button onclick=\"location.href='/shutdown'\">Shutdown Server</button></body></html>";
    server.send(200, "text/html", html);
}

// static void handleButton() {
//     Serial.println("Button was clicked!");
//     server.send(200, "text/html", "<p>Button was clicked!</p>");
// }

static void handleSubmit() {
    if (server.method() == HTTP_POST) {
        String field1 = server.arg("field1");
        String field2 = server.arg("field2");
        Serial.println("Field 1: " + field1);
        Serial.println("Field 2: " + field2);
        String response = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>ESP8266 AP</title></head><body><h1>Data Received</h1><p>Field 1: " + field1 + "</p><p>Field 2: " + field2 + "</p><button onclick=\"location.href='/'\">Go to Main Page</button><button onclick=\"location.href='/shutdown'\">Shutdown Server</button></body></html>";
        server.send(200, "text/html", response);
    } else {
        server.send(405, "text/html", "<h1>405 Method Not Allowed</h1>");
    }
}

static void handleShutdown() {
    server.send(200, "text/html", "<h1>Server is shutting down...</h1>");
    delay(1000); // Krótkie opóźnienie na wyświetlenie wiadomości
    server.stop();
    WiFi.softAPdisconnect(true);
    Serial.println("Server stopped and AP disconnected");
    web_status = false;
}