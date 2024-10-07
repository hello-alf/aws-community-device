#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include <Arduino.h>
#include <WiFi.h>

#include "network_config.h"

void connectWiFi() {
  Serial.print("Conectando a Wi-Fi...");
  WiFi.begin(WIFI_ID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conexión exitosa!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP()); 
}

String getMacAddress() {
  String serialNumber = WiFi.macAddress();
  return serialNumber;
}

#endif