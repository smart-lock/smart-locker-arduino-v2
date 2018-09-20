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
      if (_handler != NULL) {
        _handler->onConnect();
      }
    } else {
      Serial.print("failed, rc=");
      Serial.print(client->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void BaseMQTT::setHandler(BaseMQTTHandler *handler) {
  _handler = handler;
}

BaseMQTT::BaseMQTT(Client& espClient, const char *domain, const uint16_t port) {
  this->client = new PubSubClient(domain, port, espClient);
  this->client->setCallback([this](char* topic, byte* payload, unsigned int length) {
    if (this->_handler != NULL) {
      this->_handler->onMessage(topic, payload, length);
    }
  }); 
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