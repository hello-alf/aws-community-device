#include <Arduino.h>
#include <WiFi.h>

#include "network_config.h"
#include "wifi_connection.h"

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
