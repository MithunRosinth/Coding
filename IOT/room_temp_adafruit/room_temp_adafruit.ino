const int LM_35 = A0;  
int input_val = 0;
float temp = 0;

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define WIFI_SSID ""
#define WIFI_PASS ""
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME ""
#define MQTT_PASS ""
Adafruit_MQTT_Publish roomtemp = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/roomtemp");

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
   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
   MQTT_connect();
   input_val = analogRead(LM_35);
   temp = (5.0 * input_val * 100.0) / 1024; 
   Serial.print("Temperature is : " );                       
   Serial.println(temp);
   roomtemp.publish(temp);
   delay(1000);       
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
