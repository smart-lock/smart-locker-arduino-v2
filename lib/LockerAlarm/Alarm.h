#ifndef Alarm_h
#define Alarm_h

#include "Arduino.h"
#include "SystemComponent.h"

class Alarm: public ISystemComponent
{
  public:
    Alarm(const int pin);
    void printHello();

    virtual void setup();
    virtual void loop();

    void soundAlarm();
    void stopAlarm();

    bool isActive();
  private:
    int _pin;
    int _active;
    unsigned long _lastCycle;
};

#endif