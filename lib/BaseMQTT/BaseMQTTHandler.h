#ifndef BaseMQTTHandler_h
#define BaseMQTTHandler_h

#include <Arduino.h>
#include <PubSubClient.h>

class BaseMQTTHandler {
  public:
    virtual void onConnect();
    virtual void onMessage(char* topic, byte* payload, unsigned int length);
};

#endif