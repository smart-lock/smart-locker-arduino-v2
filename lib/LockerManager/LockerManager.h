#ifndef LockerManager_h
#define LockerManager_h
#include <BaseMQTTHandler.h>
#include <PubSubClient.h>
#include <SystemComponent.h>
#include <BaseMQTT.h>

#include <Locker.h>

struct LockerPinGroup {
  int groupId;
  int switchPin;
  int servoPin;
  int buzzerPin;
};

class LockerManager: public BaseMQTTHandler, public ISystemComponent {
  public:
    LockerManager(std::vector<LockerPinGroup> lockerPinGroups, BaseMQTT *baseMQTT);
    void init();
    virtual void loop();
    virtual void setup();
  private:
    std::vector<Locker*> _lockers;

    virtual void onConnect();
    virtual void onMessage(char* topic, byte* payload, unsigned int length);
    
    Locker* getLockerById(char id);
    BaseMQTT *_baseMQTT;
};

#endif