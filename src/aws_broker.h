#ifndef AWS_CONNECTION_H
#define AWS_CONNECTION_H

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

extern WiFiClientSecure net;
extern PubSubClient client;

void callback(char* topic, byte* payload, unsigned int length);
void connectAWS();
void reconnectAWS();
void publishData(char *data);

#endif