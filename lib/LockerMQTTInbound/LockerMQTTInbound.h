#ifndef LockerMQTTInbound_h
#define LockerMQTTInbound_h

#include "Arduino.h"

void callback(char* topic, byte* payload, unsigned int length);

#endif