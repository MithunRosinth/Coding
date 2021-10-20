#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define WIFI_SSID ""
#define WIFI_PASS ""
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "mithun_amrita"
#define MQTT_PASS "aio_IjSA31izy7A2htp4iM5KjAkYWaUI"

int led = D7;
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
Adafruit_MQTT_Subscribe onoff = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/ONOF");
Adafruit_MQTT_Publish LightsStatus = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/LightsStatus");

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("\n\nConnecting Wifi>");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  digitalWrite(LED_BUILTIN, LOW);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(">");
    delay(50);
  }
  Serial.println("OK!");
  mqtt.subscribe(&onoff);
  pinMode(led, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(led, LOW);

}

void loop()
{
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
        digitalWrite(led, HIGH);
        LightsStatus.publish("ON");
      }
      else if (!strcmp((char*) onoff.lastread, "OFF"))
      {
        digitalWrite(led, LOW);
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
