#include "Arduino.h"
#include "SimpleMQTT.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

void SimpleMQTT::reconnect() {
  // Loop until we're reconnected
  while (!_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connecthrome
    if (_client.connect(_id, _user, _pass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

SimpleMQTT::SimpleMQTT(WiFiClient wifiClient, const char *id, const char *user, const char *pass, const char *ip, uint16_t port, MQTT_CALLBACK_SIGNATURE) {
  PubSubClient c(wifiClient);
  _client = c;
  _client.setServer(ip, port);
  _client.setCallback(callback);

  _id = id;
  _user = user;
  _pass = pass;
}

void SimpleMQTT::loop() {
  if (!_client.connected()) {
    reconnect();
  }
  _client.loop();
}