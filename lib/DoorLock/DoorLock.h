#ifndef DoorLock_h
#define DoorLock_h
#include <SystemComponent.h>
#include <Servo.h>

class DoorLock: public ISystemComponent {
  public:
    DoorLock(uint8_t servoPin);
    virtual void loop();
    virtual void setup();
    void lock();
    void unlock();
    bool isLocked();
  private:
    bool _locked;
    Servo _lockServo;
    int _servoPin;
};

#endif