#include <BaseMQTT.h>
#include <PubSubClient.h>
#include <Arduino.h>

void BaseMQTT::reconnect() {
  // Loop until we're reconnected
  while (!_client->connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connecthrome
    if (_client->connect(_id, _user, _pass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(_client->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

BaseMQTT::BaseMQTT(Client& espClient, char *domain, uint16_t port, MQTT_CALLBACK_SIGNATURE) {
  _domain = domain;
  _port = port;
  _espClient = espClient;

  _client = new PubSubClient(_domain, _port, callback, espClient);
}


void BaseMQTT::setAuthentication(char *id, char *user, char *pass) {
  _id = id;
  _user = user;
  _pass = pass;
}

void BaseMQTT::setup() {
  
}

void BaseMQTT::loop() {
  if (!_client->connected()) {
    reconnect();
  }
  _client->loop();
}