#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define WIFI_SSID "VVMC_Guest"
#define WIFI_PASS "12345678"
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "mithun_amrita"
#define MQTT_PASS "aio_QhUK220MMrwcrw3FzpROLxrTW1nY"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
// subscribe to valve status feed to keep track on the valve
Adafruit_MQTT_Subscribe valve_status = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/valve_status");
// publish to the feed in case any changes are made due to change in water level
Adafruit_MQTT_Publish valve_action = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/valve_action");
// publish to water level feed periodically
Adafruit_MQTT_Publish water_level = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/water_level");

// Ultrasonic Sensor setup
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3void
long duration;
int distance; 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.print("\n\nConnecting Wifi>");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(">");
    delay(50);
  }
  Serial.println("OK!");
  mqtt.subscribe(&valve_status);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  MQTT_connect();
  Adafruit_MQTT_Subscribe * subscription;
  Serial.print("\n\nSubscribed Successfully");
  while ((subscription = mqtt.readSubscription(5000)))
  {
    if (subscription == &valve_status)
    {
      Serial.print("hello");
      delayMicroseconds(10);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance= duration*0.034/2;
      Serial.println(distance);
      if (strcmp((char*) valve_status.lastread, "ON"))
          {
        Serial.print("\n\nValve is open");
      }
      else{
        Serial.print("\n\nValve is closed");  
      }
      if(distance<5){
        water_level.publish(100);
        Serial.print("\n\nWater Level: 100%");
        if (strcmp((char*) valve_status.lastread, "ON"))
          {
            //code to turn off the valve
            valve_action.publish("OFF");
            Serial.print("\n\nTurned off the valve");
          }
      }
      else if(distance>5){
        switch(distance){
          case 100:
              water_level.publish(20);
              Serial.print("\n\nWater Level: 20%");
              break;
          case 80:
              water_level.publish(40);
              Serial.print("\n\nWater Level: 40%");
              break;
          case 60:
              water_level.publish(60);
              Serial.print("\n\nWater Level: 60%");
              break;
          case 40:
              water_level.publish(80);
              Serial.print("\n\nWater Level: 80%");
              break;
          case 20:
              water_level.publish(90);
              Serial.print("\n\nWater Level: 90%");
              break;
          case 10:
              water_level.publish(95);
              Serial.print("\n\nWater Level: 95%");
              break;
        }
        if (strcmp((char*) valve_status.lastread, "OFF"))
          {
            //code to turn ON the valve
            valve_action.publish("ON");
            Serial.print("\n\nTurned On the Valve");
          }
      }
    }
  }  
}

void MQTT_connect()
{
  if (mqtt.connected() && mqtt.ping())
  {
    return;
  }
  int8_t ret;
  mqtt.disconnect();
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0)
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0)
    {
      ESP.reset();
    }
  }
  Serial.println("MQTT Connected!");
}
