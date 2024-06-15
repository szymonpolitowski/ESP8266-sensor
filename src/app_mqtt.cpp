#include "app_mqtt.hpp"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "mem_flash.hpp"

WiFiClient espClient;
PubSubClient client(espClient);

// static void sendTestMessage(void);
// static unsigned long msg_timestamp;

void callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char)message[i]);
    }

    Serial.println();
}

void reconnect() {
    while (!client.connected()) 
    {
        Serial.print("Attempting MQTT connection... ");

        if (client.connect(getDeviceName().c_str())) 
        {
            Serial.println("connected");
            client.subscribe("test/topic");
        } 
        else 
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void mqttInit(void)
{
    IPAddress addr_ip_mqtt_server;
    addr_ip_mqtt_server.fromString(getMqttServer().c_str());
    client.setServer(addr_ip_mqtt_server, (uint16_t)std::stoul(getMqttPort().c_str()));
    client.setCallback(callback);
    
    // msg_timestamp = millis();
}

void mqttLoop(void)
{
    // if(5000 < millis() - msg_timestamp)
    // {
    //     msg_timestamp = millis();
    //     sendTestMessage();
    // }

    if(!client.connected())
    {
        reconnect();
    }
    client.loop();
}

// static void sendTestMessage(void)
// {
//     String topic = "test/";
//     topic += getDeviceName().c_str();
//     topic += "/temperature";
//     String payload = "25.6";

//     client.publish(topic.c_str(), payload.c_str());
//     Serial.println("MQTT Publish topic: " + topic);
//     Serial.println("MQTT Publish payload: " + payload);
// }