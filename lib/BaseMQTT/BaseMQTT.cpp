#include <BaseMQTT.h>
#include <BaseMQTTHandler.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <functional>

void BaseMQTT::reconnect() {
  // Loop until we're reconnected
  while (!client->connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connecthrome
    if (client->connect(_id, _user, _pass)) {
      Serial.println("connected");
      _handler->onConnect(client);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

BaseMQTT::BaseMQTT(Client& espClient, const char *domain, const uint16_t port, BaseMQTTHandler *handler) {
  this->client = new PubSubClient(domain, port, espClient);
  this->client->setCallback([handler](char* topic, byte* payload, unsigned int length) {
    handler->onMessage(topic, payload, length);
  });
  _handler = handler;
}


void BaseMQTT::setAuthentication(const char *id, const char *user, const char *pass) {
  _id = id;
  _user = user;
  _pass = pass;
}

void BaseMQTT::setup() {
  
}

void BaseMQTT::loop() {
  if (!client->connected()) {
    reconnect();
  }
  client->loop();
}