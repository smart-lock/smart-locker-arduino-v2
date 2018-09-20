#ifndef BaseMQTT_h
#define BaseMQTT_h
#include <SystemComponent.h>
#include <Arduino.h>
#include <PubSubClient.h>

class BaseMQTT: public ISystemComponent {
  public:
    BaseMQTT(Client& espClient, const char *domain, const uint16_t port, MQTT_CALLBACK_SIGNATURE);
    virtual void setup();
    virtual void loop();
    void setAuthentication(const char *id, const char *user, const char *pass);
  private:
    const char *_id;
    const char *_user;
    const char *_pass;
    PubSubClient *_client;
    void reconnect();
};
#endif