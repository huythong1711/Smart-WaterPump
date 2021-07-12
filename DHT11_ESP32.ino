#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h> 
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
char auth[] = " xQA7hR-BVCSkUAtNseMXerPnNk6PrpNu";
char ssid[] = "Trọ TQT";
char pass[] = "12345678";
#define DHTTYPE DHT11
#define DHTPIN 14
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}
void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(OUTA, OUTPUT);
  timer.setInterval(1000L, sendSensor);
  Blynk.begin(auth, ssid, pass);
}
void loop()
{
  Blynk.run();
  timer.run();
  
}
