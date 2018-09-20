#ifndef Locker_h
#define Locker_h

#include <SystemComponent.h>
#include <Alarm.h>
#include <DoorSensor.h>
#include <DoorLock.h>

class LockerStateListener {
  public:
    virtual void onStateChange(char id);
};

class Locker: public ISystemComponent, public DoorSensorHandler {
  public:
    Locker(char id, int switchPin, int servoPin, int buzzerPin);
    virtual void setup();
    virtual void loop();

    void lockDoor();
    void unlockDoor();

    void claimLocker();
    void freeLocker();

    void soundAlarm();
    void stopAlarm();
    void sudoStopAlarm();

    char id;

    void setLockerStateListener(LockerStateListener *lockerStateListener);

    bool isBusy();
    bool isClosed();
    bool isLocked();
    bool isAlarmActive();
  private:
    Alarm *_alarm;
    DoorSensor *_doorSensor;
    DoorLock *_doorLock;
    bool _busy;
    LockerStateListener *_lockerStateListener;

    virtual void onOpen();
    virtual void onClose();

    void printState();
    void reportToStateListener();
};

#endif