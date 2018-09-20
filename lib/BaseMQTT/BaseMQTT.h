#ifndef BaseMQTT_h
#define BaseMQTT_h
#include <SystemComponent.h>
#include <Arduino.h>
#include <PubSubClient.h>

class BaseMQTT: public ISystemComponent {
  public:
    BaseMQTT(Client& espClient, char *domain, uint16_t port, MQTT_CALLBACK_SIGNATURE);
    virtual void setup();
    virtual void loop();
    void setAuthentication(char *id, char *user, char *pass);
  private:
    char *_domain;
    uint16_t _port;
    char *_id;
    char *_user;
    char *_pass;
    Client& _espClient;
    PubSubClient *_client;
    void reconnect();
};
#endif