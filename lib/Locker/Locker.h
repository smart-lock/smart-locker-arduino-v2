#ifndef Locker_h
#define Locker_h

#include <SystemComponent.h>
#include <Alarm.h>
#include <DoorSensor.h>
#include <DoorLock.h>

class Locker: public ISystemComponent, public DoorSensorHandler {
  public:
    Locker(char id, int switchPin, int servoPin, int buzzerPin);
    virtual void setup();
    virtual void loop();

    void lockDoor();
    void unlockDoor();

    void claimLocker();
    void freeLocker();

    char id;
  private:
    Alarm *_alarm;
    DoorSensor *_doorSensor;
    DoorLock *_doorLock;
    bool _busy;

    virtual void onOpen();
    virtual void onClose();
};

#endif