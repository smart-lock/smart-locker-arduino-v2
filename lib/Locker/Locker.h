#ifndef Locker_h
#define Locker_h

#include <SystemComponent.h>
#include <Alarm.h>
#include <DoorSensor.h>
#include <DoorLock.h>

class Locker: public ISystemComponent, public DoorSensorHandler {
  public:
    Locker(Alarm *alarm, DoorSensor *doorSensor, DoorLock *doorLock);
    virtual void setup();
    virtual void loop();

    void lockDoor();
    void unlockDoor();

  private:
    Alarm *_alarm;
    DoorSensor *_doorSensor;
    DoorLock *_doorLock;

    virtual void onOpen();
    virtual void onClose();
};

#endif