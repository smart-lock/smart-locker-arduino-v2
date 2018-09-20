#ifndef LockerMQTTInbound_h
#define LockerMQTTInbound_h

#include <Arduino.h>
void mqttCallback(char* topic, byte* payload, unsigned int length);

#endif