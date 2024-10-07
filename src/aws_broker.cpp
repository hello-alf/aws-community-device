#include <Arduino.h>
#include <ArduinoJson.h>

#include "aws_broker.h"

#include "aws_cert.h"
#include "aws_private_key.h"
#include "aws_ca_cert.h"
#include "thing_config.h"
#include "broker_config.h"

void callback(char* topic, byte* payload, unsigned int length){
  String incomming = "";
  Serial.print("Mensaje recibido desde -> ");
  Serial.print(topic);
  Serial.println("");
  Serial.println("Mensaje -> "+incomming);
  
  JsonDocument doc;
  deserializeJson(doc, incomming);
}

void connectAWS() {
  // Configuración de AWS IoT
  Serial.println("Iniciando conexión a AWS IoT Core!");
  
  net.setCACert(AWS_CA_CERT);
  net.setCertificate(AWS_CERT);
  net.setPrivateKey(AWS_PRIVATE_KEY);

  client.setServer(AWS_IOT_ENDPOINT, AWS_IOT_PORT);
  client.setCallback(callback);

  // while (!client.connect(THINGNAME)) {
  //   Serial.print(".");
  //   delay(1000);
  //   Serial.println(client.state()); 
  // }

  // Serial.println("Conectado a AWS IoT Core!");
}

void reconnectAWS()
{
  Serial.print("Intentando conexión Mqtt...");

  if(client.connect(THINGNAME)){
    Serial.println("Conectado a aws!");
    
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