#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define WIFI_SSID ""
#define WIFI_PASS ""
#define MQTT_SERV "192.168.68.116"
#define MQTT_PORT 1883
#define MQTT_NAME ""
#define MQTT_PASS ""

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
Adafruit_MQTT_Subscribe test = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/ONOF");


void setup() {
  Serial.begin(9600);
  Serial.print("\n\nConnecting Wifi>");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(">");
    delay(50);
  }
  Serial.println("OK!");
  mqtt.subscribe(&test);

}

void loop() {
  

}
