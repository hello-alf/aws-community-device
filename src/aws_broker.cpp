#include <Arduino.h>
#include <ArduinoJson.h>

#include "aws_broker.h"

#include "aws_cert.h"
#include "aws_private_key.h"
#include "aws_ca_cert.h"
#include "thing_config.h"
#include "broker_config.h"

#include "wifi_connection.h"
#include "led_rgb.h"

void callback(char* topic, byte* payload, unsigned int length){
  String incomming = "";

  for (int i = 0; i < length; i++) {
    incomming += (char)payload[i];
  }
  incomming.trim();
  Serial.print("Mensaje recibido desde -> ");
  Serial.print(topic);
  Serial.println("");
  Serial.println("Mensaje -> "+incomming);
  
  JsonDocument doc;
  deserializeJson(doc, incomming);

  if (doc["red"].is<int>() && doc["green"].is<int>() && doc["blue"].is<int>()) {
    int red = doc["red"];
    int green = doc["green"];
    int blue = doc["blue"];

    // Asegúrate de que los valores estén entre 0 y 255

    Serial.print("Valores recibidos -> Red: ");
    Serial.print(red);
    Serial.print(", Green: ");
    Serial.print(green);
    Serial.print(", Blue: ");
    Serial.println(blue);

    // Aquí puedes actualizar tu LED RGB con los valores recibidos
    // Asumiendo que tienes una función para actualizar el LED RGB
    updateRGBLed(red, green, blue);
  } else {
    Serial.println("El campo 'message' no está presente en el JSON.");
  }
}

void connectAWS() {
  Serial.println("Iniciando conexión a AWS IoT Core!");
  
  net.setCACert(AWS_CA_CERT);
  net.setCertificate(AWS_CERT);
  net.setPrivateKey(AWS_PRIVATE_KEY);

  client.setServer(AWS_IOT_ENDPOINT, AWS_IOT_PORT);
  client.setCallback(callback);

}

void reconnectAWS()
{
  Serial.println("Intentando conexión Mqtt por reconeccion...");

  if(client.connect(THINGNAME)){
    Serial.println("Conectado a aws!");
    Serial.println(getMacAddress());
    char topic[40];
    String topic_aux = "home/led/" + getMacAddress();
    topic_aux.toCharArray(topic, 40);
    client.subscribe(topic);
    
  }else{
    Serial.print("falló :( con error -> ");
    Serial.print(client.state());
    Serial.println(" Intentamos de nuevo en 5 segundos");
    delay(2000);
  }
}

void publishData(char *data) {

  const String topic = "home/temperature";

  client.publish(topic.c_str(), data);
}