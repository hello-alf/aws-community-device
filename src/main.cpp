#include <Arduino.h>

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include "wifi_connection.h"
#include "aws_broker.h"
#include "measure.h"
#include "led_rgb.h"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

#define LED_PIN       2  // Pin conectado al LED

int buttonState = 0;
int lastButtonState = HIGH;


unsigned long previousMillis = 0;  // Almacena el último tiempo que se envió información
const long interval = 10000;       // Intervalo de tiempo (10 segundos)

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  connectWiFi();
  connectAWS();
  configDHT();
  configRGBLeds();
  
}

void loop() {

  if(!client.connected()){
    reconnectAWS();
  }

  client.loop();

  // Obtén el tiempo actual
  unsigned long currentMillis = millis();

  // Si han pasado más de 10 segundos, realiza las acciones
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Actualiza el tiempo de la última ejecución

    digitalWrite(LED_PIN, LOW);

    char buffer[512]; 
    measureDHT(buffer, sizeof(buffer));

    digitalWrite(LED_PIN, HIGH);
    publishData(buffer);
  }

}