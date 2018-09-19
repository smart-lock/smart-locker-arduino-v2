#ifndef Locker_h
#define Locker_h

#include <SystemComponent.h>
#include <Alarm.h>
#include <DoorSensor.h>

class Locker: public ISystemComponent {
  public:
    Locker(Alarm *alarm, DoorSensor *doorSensor, DoorLock *doorLock);
    void setup();
    void loop();
  private:
    Alarm *_alarm;
    DoorSensor *_doorSensor;
    DoorLock *_doorLock;
};

#endif