#ifndef SimpleMQTT_h
#define SimpleMQTT_h

#include "Arduino.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

class SimpleMQTT {
  public:
    SimpleMQTT(WiFiClient wifiClient, const char *id, const char *user, const char *pass, const char *ip, uint16_t port, MQTT_CALLBACK_SIGNATURE);
    void loop();
  private:
    PubSubClient _client;
    const char *_id;
    const char *_user;
    const char *_pass;
    void reconnect();
};

#endif