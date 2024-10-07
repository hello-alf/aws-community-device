#ifndef DHT_MEASUREMENT_H
#define DHT_MEASUREMENT_H

#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>

extern float humidity;
extern float temperature;

#define DHTPIN 23
#define DHTTYPE DHT11

void configDHT();
void measureDHT(char* buffer, size_t bufferSize);

#endif