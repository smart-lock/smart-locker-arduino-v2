#ifndef BaseMQTT_h
#define BaseMQTT_h
#include <SystemComponent.h>
#include <BaseMQTTHandler.h>
#include <Arduino.h>
#include <PubSubClient.h>
#include <functional>

#define ON_CONNECT_SIGNATURE std::function<void(PubSubClient *client)> onConnect
class BaseMQTT: public ISystemComponent {
  public:
    BaseMQTT(
      Client& espClient,
      const char *domain,
      const uint16_t port,
      BaseMQTTHandler *handler
    );
    virtual void setup();
    virtual void loop();
    void setAuthentication(const char *id, const char *user, const char *pass);
    PubSubClient *client;
  private:
    const char *_id;
    const char *_user;
    const char *_pass;
    void reconnect();
    BaseMQTTHandler *_handler;
};
#endif