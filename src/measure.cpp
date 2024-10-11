#include <Arduino.h>
#include <ArduinoJson.h>
#include "measure.h"
#include "thing_config.h"

DHT dht(DHTPIN, DHTTYPE);

float humidity = 0;
float temperature = 0;

void configDHT() {
  dht.begin();
}

void measureDHT(char* buffer, size_t bufferSize) {
  delay(2000);
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  StaticJsonDocument<200> doc;
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["device_id"] = THINGNAME;

  serializeJson(doc, buffer, bufferSize);
}