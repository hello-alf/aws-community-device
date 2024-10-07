#include <Arduino.h>

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include "wifi_connection.h"
#include "aws_broker.h"
#include "measure.h"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

#define LED_PIN                2  // Pin conectado al LED
const int buttonPin = 18; // Pin conectado al botón

int buttonState = 0;
int lastButtonState = HIGH; 

float humidity = 0;
float temperature = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  connectWiFi();
  connectAWS();
  configDHT();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // for (int i = 0; i < 5; i++) {
  //   Serial.println("Cambiando el estado del LED");
  //   digitalWrite(LED_PIN, HIGH);
  //   delay(1000); // 1000 ms encendido
  //   digitalWrite(LED_PIN, LOW);
  //   delay(1000); // 1000 ms apagado
  // }

  if(!client.connected()){
    reconnectAWS();
  }

  client.loop();

  digitalWrite(LED_PIN, LOW);

  // buttonState = digitalRead(buttonPin);
  
  // if (buttonState == LOW && lastButtonState == HIGH) {
  //   // El pulsador acaba de ser presionado
  //   Serial.println("¡Botón presionado!");
  //   // Aquí puedes ejecutar la acción que desees
  // }

  // if (buttonState == HIGH && lastButtonState == LOW) {
  //   Serial.println("¡Botón soltado!");
  // }

  // // Guardar el estado actual como el último estado, para la siguiente iteración
  // lastButtonState = buttonState;

  // delay(100); // 1000 ms apagado

  char buffer[512]; 
  measureDHT(buffer, sizeof(buffer));

  digitalWrite(LED_PIN, HIGH);
  publishData(buffer);

  delay(10000);

}