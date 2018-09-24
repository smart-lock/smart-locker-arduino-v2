#ifndef LockerManager_h
#define LockerManager_h
#include <BaseMQTTHandler.h>
#include <PubSubClient.h>
#include <SystemComponent.h>
#include <BaseMQTT.h>
#include <LockerCluster.h>
#include <Locker.h>
#include <BackendService.h>
#include <View.h>

class LockerManager: public BaseMQTTHandler, public ISystemComponent, public LockerStateListener {
  public:
    LockerManager(BaseMQTT *baseMQTT, BackendService *backendService, View *view);
    void init();
    virtual void loop();
    virtual void setup();
    virtual void onStateChange(char id);
  private:
    std::vector<Locker*> _lockers;
    LockerCluster *_lockerCluster;
    Locker* getLockerByIdInCluster(char idInCluster);
    BaseMQTT *_baseMQTT;
    BackendService *_backendService;
    View *_view;
    bool _loading;
    
    virtual void onConnect();
    virtual void onMessage(char* topic, byte* payload, unsigned int length);
    void publishLockerReport(Locker* locker);
    void fetchLockerCluster();
};

#endif