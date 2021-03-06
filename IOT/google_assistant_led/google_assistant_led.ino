#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define WIFI_SSID ""
#define WIFI_PASS ""
#define MQTT_SERV ""
#define MQTT_PORT 1883
#define MQTT_NAME ""
#define MQTT_PASS ""

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
Adafruit_MQTT_Subscribe onoff = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/ONOF");
Adafruit_MQTT_Publish LightsStatus = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/LightsStatus");

void setup()
{
  Serial.begin(9600);
  Serial.print("\n\nConnecting Wifi>");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(">");
    delay(50);
  }
  Serial.println("OK!");
  mqtt.subscribe(&onoff);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

}

void loop()
{
    // ping adafruit io a few times to make sure we remain connected
  if(! mqtt.ping(3)) {
    // reconnect to adafruit io
    if(! mqtt.connected())
      connect();
  }
  MQTT_connect();
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    if (subscription == &onoff)
    {
      Serial.print("onoff: ");
      Serial.println((char*) onoff.lastread);
      if (!strcmp((char*) onoff.lastread, "ON"))
      {
        digitalWrite(LED_BUILTIN, HIGH);
        LightsStatus.publish("ON");
      }
      else if (!strcmp((char*) onoff.lastread, "OFF"))
      {
        digitalWrite(LED_BUILTIN, LOW);
        LightsStatus.publish("OFF");
      }
      else
      {
        LightsStatus.publish("ERROR");
      }
    }
    else
    {
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
