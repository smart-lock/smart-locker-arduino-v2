#ifndef LockerManager_h
#define LockerManager_h
#include <BaseMQTTHandler.h>
#include <PubSubClient.h>

#include <Locker.h>

class LockerManager: public BaseMQTTHandler {
  public:
    LockerManager();
    void init();
  private:
    std::vector<Locker> lockers;

    virtual void onConnect(PubSubClient *client);
    virtual void onMessage(char* topic, byte* payload, unsigned int length);
};

#endif